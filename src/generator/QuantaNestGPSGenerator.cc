#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"
#include "detector/BambooDetectorPart.hh"
#include "generator/QuantaNestGPSGenerator.hh"
#include "generator/BambooGeneratorFactory.hh"
#include "generator/QS1RawNest.hh"

#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTable.hh>
#include <G4OpticalPhoton.hh>
#include <Randomize.hh>
#include <cassert>
#include <TH1I.h>
#include <G4ThreeVector.hh>
#include <TFile.h>
#include <TMath.h>
#include <algorithm>

#define DEBUG_GPS_GEN_PRI

GeneratorRegister<QuantaNestGPSGenerator> QuantaNestGPSGenerator::reg("QuantaNestGPSGenerator");

double ZDistribution(const double x, const double y, const double dz) //unit:mm
{
	double r = sqrt(x * x + y * y)/10;//unit cm for r
	double f = 0;
	double g0 = 3.06342, g1 = 0.00517871, g2 = 0.00014236;
	double Gr = g0 + g1 * r + g2 * r * r;
	double r0 = 0.438348, r1 = 53.2886, r2 = 3.78665, r3 = 0.00313052;
	double Rr = r0 / (exp((r - r1) / r2) + 1) + r3 * r;
	double k0 = 26.8231, k1 = -0.118418, k2 = -0.00364175, k3 = 0.000145804;
	double Kr = 1.6*(k0 + k1 * r + k2 * r * r + k3 * r * r * r);
	if (dz > 0 && dz < Gr) f = 1. / Gr + Rr / (Kr / 360. * 3.73) * exp(-(Gr - dz) / (Kr / 360.*3.73));
	return f;
}

QuantaNestGPSGenerator::QuantaNestGPSGenerator(const G4String &name)
    : BambooGenerator(name) {

	G4String Edep_str = BambooGlobalVariables::Instance()->getGeneratorParameterAsString("Edep");
	G4String Efield_str = BambooGlobalVariables::Instance()->getGeneratorParameterAsString("Efield");
	G4String Type_str = BambooGlobalVariables::Instance()->getGeneratorParameterAsString("Type");
	
    _particleGun = new G4ParticleGun();

	if (Edep_str == "")
		_Edep = 1.0; // keV
	else
		_Edep = BambooUtils::evaluate(Edep_str);

	if (Efield_str == "")
		_Efield = 1.03; // V/cm
	else
		_Efield = BambooUtils::evaluate(Efield_str);

	if (Type_str == "er")
		_rType = PRecoilType::rtER;
	else
		_rType = PRecoilType::rtNR;
}

QuantaNestGPSGenerator::~QuantaNestGPSGenerator() { 
	delete _particleGun; 
}

////////////////////////////////////////////////////
// Qing's private functions
////////////////////////////////////////////////////
Double_t QuantaNestGPSGenerator::getNormalizedCrossSection(G4double theta)
{
    // hardcoded
    Double_t ref_theta              = TMath::ATan2(288.,316.);
    return TMath::Cos(ref_theta-theta);
}

Double_t QuantaNestGPSGenerator::getNormalizedFlux(G4double theta)
{
    // following arXiv: 1606.06907
    G4double n              = 3.01;
    return TMath::Power(TMath::Cos(theta), n-1.);
}

Double_t QuantaNestGPSGenerator::getRandomTheta()
{
    G4double theta, rvs=1., upperlimit=0.;
    while(rvs>upperlimit)
    {
        theta               = G4UniformRand()*3.141592653/2.; // in rad
        rvs                 = G4UniformRand();
        upperlimit          = getNormalizedFlux(theta) * getNormalizedCrossSection(theta);
    }
    // return in rad
    return theta;
}

Double_t QuantaNestGPSGenerator::getRandomTranslation(G4double theta)
{
    // hardcoded
    Double_t ref_theta              = TMath::ATan2(288., 316.);
    return TMath::Sqrt(288.*288.+316.*316.)/2.*TMath::Cos(ref_theta-theta)*cm*G4UniformRand();
}

Double_t QuantaNestGPSGenerator::getRandomEnergy(G4double theta, G4double lower, G4double upper)
{
    G4double E, rvs=1., upperlimit=0.;
    // hardcoded hyperparameters
    G4double I0                 = 72.5/10000.;
    G4double E0                 = 4.29;
    G4double n                  = 3.01;
    G4double epsilon            = 854.;

    /////////////////////////////
    G4double costheta               = TMath::Cos(theta);
//    G4double val_max                = 0.14*TMath::Power(lower,-2.7)*(1./(1.+1.1*lower*costheta/115.)+0.054/(1+1.1*lower*costheta/850.)); // Gaissar flux
    G4double val_max                = I0*(n-1)/(E0+lower)/(1.+lower/epsilon);
    while(rvs>upperlimit)
    {
        E                           = G4UniformRand()*(upper-lower)+lower;
        rvs                         = G4UniformRand()*val_max;
        // some hardcoding
//        upperlimit                  = 0.14*TMath::Power(E,-2.7)*(1./(1.+1.1*E*costheta/115.)+0.054/(1+1.1*E*costheta/850.)); //Gaissar flux
        upperlimit                  = I0*(n-1)*TMath::Power(E0+lower, n-1) / TMath::Power(E0+E, n) * TMath::Power(1.+E/epsilon,-1.); // Shuklar flux
    }
    // return in GeV
    return E*GeV;
}

///////////////////////////////////////////////////

void QuantaNestGPSGenerator::GeneratePrimaries(G4Event *anEvent){
    // generate muon only
    G4cout<<"Cosmic ray muon generator used!"<<G4endl;
    //////////////////////////////////////////
    // Qing's modification
    //////////////////////////////////////////
    // hardcoded values
    G4double EnergyLower            = 0.5*GeV;
    G4double EnergyUpper            = 1000.*GeV;
    G4double Source2CoilDistance    = 2500.*mm;
    // initiate
    G4double posX=0, posY=0, posZ=Source2CoilDistance;
    G4double dirX=0, dirY=0, dirZ=-1;
    // Randomize the theta
    G4double rvsTheta               = getRandomTheta(); // in rad
    G4double rvsTranslation         = getRandomTranslation(rvsTheta); // in mm
    // debug
//    G4cout << "rvsTheta = " << rvsTheta/rad << " rad" << G4endl;
//    G4cout << "rvsTranslation = " << rvsTranslation/mm << " mm" << G4endl;
    // Calculate the direction and start position
    // assuming only generating particles on XZ plane with direction of X and Z always negative
    // because the detector geometry is axial symmetrical
    dirX                            = -TMath::Sin(rvsTheta);
    dirZ                            = -TMath::Cos(rvsTheta);
    posX                            = Source2CoilDistance*TMath::Sin(rvsTheta);
    posZ                            = Source2CoilDistance*TMath::Cos(rvsTheta);
    posX                           += rvsTranslation*TMath::Cos(rvsTheta);
    posZ                           += rvsTranslation*(-TMath::Sin(rvsTheta));
    // sample the energy
    G4double rvsEnergy              = getRandomEnergy(rvsTheta, EnergyLower, EnergyUpper);
    // set gun
    auto particleTable              = G4ParticleTable::GetParticleTable();
    _particleGun->SetParticleDefinition(particleTable->FindParticle("mu-"));
    _particleGun->SetParticleEnergy(rvsEnergy);
    _particleGun->SetParticlePosition(G4ThreeVector(posX, posY, posZ));
    _particleGun->SetParticleMomentumDirection(G4ThreeVector(dirX,dirY,dirZ));
    _particleGun->GeneratePrimaryVertex(anEvent);

}


/*
void QuantaNestGPSGenerator::GeneratePrimaries(G4Event *anEvent) {
	double xx, yy, zz, sigmaR;
	bool IsUniform;
//	int stepZ = 37;//total 4mm, 0.1mm one step
	int stepZ = 1;// no Z distribution
	double minheight = 367.9 - 3.73;//2.7mm below anode(367.9mm)
	double maxheight = 367.9;//anode
	BambooGlobalVariables::Instance()->getGLHSigmaR(sigmaR);
	BambooGlobalVariables::Instance()->getGLHIsUniform(IsUniform);
	int np = 0;

#ifdef DEBUG_GPS_GEN_PRI
	G4cout << "*** DEBUG *** _particleGun->GetParticleEnergy(): " 
		<< _particleGun->GetParticleEnergy() << G4endl;	
	G4cout << "*** DEBUG *** _particleGun->GetNumberOfParticles(): " 
		<< _particleGun->GetNumberOfParticles() << G4endl;	
#endif	
	if (IsUniform) {
		G4cout << "Generate Uniform sources" << G4endl;
		////for uniform simulation
		BambooGlobalVariables::Instance()->getGLHPhotonNumber(np);
//		np = 2000;//for uniform
		// first get the input xx, yy, zz as the boundary
		BambooGlobalVariables::Instance()->getGLHLightSourcePos(xx, yy, zz);
		double rr_max = std::max(xx, yy);
		double rr_min = std::min(xx, yy);
		const auto posXYZ   = QS1RawNest::GenAbsolutePosition2(rr_min, rr_max, zz-SigmaR, zz+SigmaR);
		xx = posXYZ.getX();
		yy = posXYZ.getY();
		zz = posXYZ.getZ();
		// debug only, remove later
		G4cout << "=========================================" << G4endl;
		G4cout << "==>> Qing debug: " << G4endl;
		G4cout << "xx = " << xx << "; yy = " << yy << "; zz = " << zz << G4endl;
		G4cout << "generate number of photon = " << np << G4endl;
		G4cout << "=========================================" << G4endl;
	}
	else {
		G4cout << "Generate PointLight sources" << G4endl;
		////for point pos light source simulation
		np = 1000;//GGNN
		BambooGlobalVariables::Instance()->getGLHLightSourcePos(xx, yy, zz);
	}
	
//	zz = 0;//clear z
	G4cout << "xx=" << xx << ",yy=" << yy << ",zz=" << zz <<",np="<<np<<",SigmaR="<<sigmaR<< G4endl;
	if (sigmaR == 0) G4cerr << "SigmaR==0mm, are you sure?" << G4endl;
	if (sigmaR <0) {
		Double_t sigmaMin = 0.1 * mm;
		Double_t sigmaMax = 3.0 * mm;
		TRandom3 rs(0);
		sigmaR = rs.Rndm()*(sigmaMax-sigmaMin)+sigmaMin;
	}
#ifdef DEBUG_GPS_GEN_PRI
	G4cout << "*** DEBUG *** QuantaNestGPSGenerator::_Edep: " 
		<< _Edep << "(keV)"<<G4endl;	
	G4cout << "*** DEBUG *** QuantaNestGPSGenerator::_Efield: " 
		<< _Efield << "(V/cm)"<<G4endl;	
	G4cout << "*** DEBUG *** QuantaNestGPSGenerator::_rType: " 
		<< _rType <<G4endl;			
#endif
	// !!! still not fluctuation
#ifdef DEBUG_GPS_GEN_PRI
	G4cout<<"****************************************" << G4endl;
#endif
	for (G4int i = 0; i < stepZ; i++){
//		int n_step = (int)(np * ZDistribution(xx, yy, (maxheight-minheight) / stepZ * i) / stepZ);
		int n_step = (int)(np/stepZ); // no z distribution
		G4cout << "i:" << i << ", n_step:" << n_step << G4endl;
		if (n_step > 0) {
			auto h = QS1RawNest::GenTimingProfile(n_step, _rType);
			if(h == nullptr) continue;
			auto tp = QS1RawNest::GenTimingPhoton(h);
			if(((int)tp.size()) != n_step) continue;
			auto ud = QS1RawNest::GenUniformDirection(n_step);
			if(((int)ud.size()) != n_step) continue;
			for (int ii = 0; ii < n_step; ii++) {
				//auto pos = QS1RawNest::GenPointAbsolutePosition(0.1 * mm, xx * mm, yy * mm, minheight * mm + (maxheight - minheight) / stepZ * i * mm);//Sphere area r,x,y,z total 4mm for Z
//				auto pos = QS1RawNest::GenCylinderAbsolutePosition(sigmaR * mm, xx * mm, yy * mm, minheight * mm + (maxheight - minheight) / stepZ * i * mm, 0.1 * mm);//cylinder area r,x,y,z,h total 4mm for Z,r=2.97mm for dt=800us
				auto pos = QS1RawNest::GenCylinderAbsolutePosition(sigmaR * mm, xx * mm, yy * mm, zz * mm, 0.1 * mm);//no z-distribution
				_particleGun->SetParticleDefinition(G4OpticalPhoton::Definition());
				_particleGun->SetParticleEnergy(6.98 * eV);
				_particleGun->SetParticlePosition(pos);
				_particleGun->SetParticleMomentumDirection(ud[ii]);
				_particleGun->SetParticleTime(tp[ii] * ns);
				_particleGun->GeneratePrimaryVertex(anEvent);
#ifdef DEBUG_GPS_GEN_PRI
				G4cout << "* PID:" << i << ", t:" << tp[i] * ns << "ns" << G4endl;
#endif
			}
			delete h;
		}
	}
#ifdef DEBUG_GPS_GEN_PRI
	G4cout<<"****************************************" << G4endl;
#endif
	
#ifdef DEBUG_GPS_GEN_PRI
	G4cout << "*** DEBUG *** _particleGun->GetParticleEnergy(): " 
		<< _particleGun->GetParticleEnergy() << G4endl;	
	G4cout << "*** DEBUG *** _particleGun->GetNumberOfParticles(): " 
		<< _particleGun->GetNumberOfParticles() << G4endl;	
#endif

   
}
*/
