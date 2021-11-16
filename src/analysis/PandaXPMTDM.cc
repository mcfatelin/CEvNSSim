#include "analysis/PandaXPMTDM.hh"
#include "analysis/PandaXPMTHit.hh"

#include <TFile.h>
#include <TTree.h>

#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4PhysicalConstants.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4THitsMap.hh>
//#include <TMath.h>
#include <iostream>

PandaXPMTDM *PandaXPMTDM::_instance = 0;

TemporaryPMTParticle::TemporaryPMTParticle()
    : _type("unknown"), _id(0), _energy(0), _px(0), _py(0), _pz(0), _x(0),
      _y(0), _z(0) {}

TemporaryPMTParticle::~TemporaryPMTParticle() {}

const std::string &TemporaryPMTParticle::getParticleType() const { return _type; }

void TemporaryPMTParticle::setParticleType(const std::string type) {
    _type = type;
} 

int TemporaryPMTParticle::getId() const { return _id; }

void TemporaryPMTParticle::setId(int i) { _id = i; }

double TemporaryPMTParticle::getEnergy() const { return _energy; }

void TemporaryPMTParticle::setEnergy(double e) { _energy = e; }

double TemporaryPMTParticle::getPx() const { return _px; }

void TemporaryPMTParticle::setPx(double v) { _px = v; }

double TemporaryPMTParticle::getPy() const { return _py; }

void TemporaryPMTParticle::setPy(double v) { _py = v; }

double TemporaryPMTParticle::getPz() const { return _pz; }

void TemporaryPMTParticle::setPz(double v) { _pz = v; }

double TemporaryPMTParticle::getX() const { return _x; }

void TemporaryPMTParticle::setX(double v) { _x = v; }

double TemporaryPMTParticle::getY() const { return _y; }

void TemporaryPMTParticle::setY(double v) { _y = v; }

double TemporaryPMTParticle::getZ() const { return _z; }

void TemporaryPMTParticle::setZ(double v) { _z = v; }

double TemporaryPMTParticle::getT() const { return _t; }

void TemporaryPMTParticle::setT(double v) { _t = v; }

PandaXPMTDM::PandaXPMTDM(bool enablePMT)
    : _rootFile(0), _mcTree(0), _recordPMT(enablePMT), _saveNullEvent(false),
      _partialSaved(false) {
    _instance = this;
}

PandaXPMTDM::~PandaXPMTDM()
{
   if (_rootFile != nullptr && _rootFile->IsOpen()) {
       _rootFile->Close();
   }
   G4cout << "PandaXPMTDM destructed." << G4endl;
}

void PandaXPMTDM::book(const std::string &name) {
    _rootFile = new TFile(name.c_str(), "RECREATE");
    if (_rootFile->IsZombie()) {
        std::cerr << "PandaXPMTDM::book: ";
        std::cerr << "problem creating ROOT file." << std::endl << std::endl;
        _rootFile = 0;
        return;
    }
    _mcTree = new TTree("mcTree", "Tree with MC info");
    _mcTree->Branch("runId", &_runId, "runId/I");
    _mcTree->Branch("eventId", &_eventId, "eventId/I");
    _mcTree->Branch("killerProcess",&killerProcess);
    _mcTree->Branch("prekillerProcess",&prekillerProcess);
    _mcTree->Branch("lastTouchableVolume",&lastTouchableVolume);
    _mcTree->Branch("lastStepPreVol",&lastStepPreVol);
    _mcTree->Branch("lastStepPostVol",&lastStepPostVol);
    _mcTree->Branch("lastStepLength",&lastStepLength);
    _mcTree->Branch("lastStepEdep",&lastStepEdep);
    _mcTree->Branch("opBoundStatus",&opBoundStatus);
    if (_recordPMT) {
      _mcTree->Branch("nPMTHits", &_nPMTHits);
      _mcTree->Branch("HitSetofPMTs", &PMTSet);
      _mcTree->Branch("PmtNumber", &_fPmtNumber);
      _mcTree->Branch("Photons", &_fPhotons);
      _mcTree->Branch("PositionX", &_fPosX);
      _mcTree->Branch("PositionY", &_fPosY);
      _mcTree->Branch("PositionZ", &_fPosZ);
      _mcTree->Branch("TimeGlobal", &_fTimeGlo);
      _mcTree->Branch("TimeLocal", &_fTimeLoc);
      _mcTree->Branch("TimeProper", &_fTimePro);
      //_mcTree->Branch("TimeDetected", &_fTimeDet);
      _mcTree->Branch("TrackID", &_fTrackID);	// PhotonID
    }
	
	//if (_recordPrimaryParticle) 
	{
        _mcTree->Branch("nPrimaries", &_nPrimaries);
        _mcTree->Branch("primaryType", &_primaryType);
        _mcTree->Branch("primaryId", &_primaryId);
        _mcTree->Branch("primaryEnergy", &_primaryEnergy);
        _mcTree->Branch("primaryPx", &_primaryPx);
        _mcTree->Branch("primaryPy", &_primaryPy);
        _mcTree->Branch("primaryPz", &_primaryPz);
        _mcTree->Branch("primaryX", &_primaryX);
        _mcTree->Branch("primaryY", &_primaryY);
        _mcTree->Branch("primaryZ", &_primaryZ);
        _mcTree->Branch("primaryT", &_primaryT); // time profile
    }

}

void PandaXPMTDM::save() {
    _mcTree->Write();
    G4cout << "PandaXPMTDM: Write data to tree..." << G4endl;
}

void PandaXPMTDM::saveNullEvent(bool t) { _saveNullEvent = t; }

void PandaXPMTDM::fillEvent(const G4Event *aEvent, bool partial) {
    if (!partial && _partialSaved)
        return;
    G4HCofThisEvent *hCthis = aEvent->GetHCofThisEvent();
    int nHitCollections = hCthis->GetNumberOfCollections();
    resetData();
    
    //add
    if (_recordPMT) 
    {
		for (int i = 0; i < nHitCollections; ++i) 
		{
            G4VHitsCollection *hitsCollection = hCthis->GetHC(i);
            if (hitsCollection->GetName().contains("pmtHitCollection")) 
            {
                auto hC = (PandaXPMTHitsCollection *)hitsCollection;
                std::cout << hitsCollection->GetSize() << std::endl;
                for (size_t j = 0; j < hitsCollection->GetSize(); ++j) 
                {
                    auto hit = (PandaXPMTHit *)hC->GetHit(j);
					
					PMTSet.push_back(hitsCollection->GetSDname());
                    _fPmtNumber.push_back(hit->GetPMTNumber());
					_fPhotons.push_back(hit->GetPhotonCount());
					
					_fPosX.push_back(hit->GetPMTPos().x() / cm);
					_fPosY.push_back(hit->GetPMTPos().y() / cm);
					_fPosZ.push_back(hit->GetPMTPos().z() / cm);
					
					_fTimeGlo.push_back(hit->GetTimes().x() / ns);
					_fTimeLoc.push_back(hit->GetTimes().y() / ns);
					_fTimePro.push_back(hit->GetTimes().z() / ns);
                    _fTrackID.push_back(hit->GetTrackID());
                    
                    _nPMTHits++;
                }
            }
        }
        //if (partial) {
            // clear the temporary particles
            //_particles = _tparticles;
            //_tparticles.clear();
		//}
    }
    
    // if (_recordPrimaryParticle)
    {
		if (!partial || _particles.size() == 0) 
		{
            // loop over all primary particles...
            int nVertex = aEvent->GetNumberOfPrimaryVertex();
            for (int iV = 0; iV < nVertex; ++iV) 
            {
                G4PrimaryVertex *vertex = aEvent->GetPrimaryVertex(iV);
                int nParticles = vertex->GetNumberOfParticle();
                double x = vertex->GetX0();
                double y = vertex->GetY0();
                double z = vertex->GetZ0();
                double t = vertex->GetT0();
                for (int ip = 0; ip < nParticles; ++ip) 
                {
                    G4PrimaryParticle *particle = vertex->GetPrimary(ip);
                    _primaryType.push_back(
                        particle->GetParticleDefinition()->GetParticleName());
                    _primaryId.push_back(particle->GetTrackID());
                    _primaryEnergy.push_back(particle->GetTotalEnergy() / keV);
                    _primaryPx.push_back(particle->GetPx() / keV);
                    _primaryPy.push_back(particle->GetPy() / keV);
                    _primaryPz.push_back(particle->GetPz() / keV);
                    _primaryX.push_back(x / mm);
                    _primaryY.push_back(y / mm);
                    _primaryZ.push_back(z / mm);
                    _primaryT.push_back(t / mm);
                    _nPrimaries++;
                }
            }
        } 
        else 
        {
            for (size_t ip = 0; ip < _particles.size(); ++ip) 
            {
                TemporaryPMTParticle &particle = _particles[ip];
                _primaryType.push_back(particle.getParticleType());
                _primaryId.push_back(particle.getId());
                _primaryEnergy.push_back(particle.getEnergy() / keV);
                _primaryPx.push_back(particle.getPx() / keV);
                _primaryPy.push_back(particle.getPy() / keV);
                _primaryPz.push_back(particle.getPz() / keV);
                _primaryX.push_back(particle.getX() / mm);
                _primaryY.push_back(particle.getY() / mm);
                _primaryZ.push_back(particle.getZ() / mm);
                _primaryT.push_back(particle.getT() / mm);
                _nPrimaries++;
            }
        }
        
        if (partial) 
        {
            // clear the temporary particles
            _particles = _tparticles;
            _tparticles.clear();
        }
    }
    
    _mcTree->Fill();
    
    if (partial) {
        resetPartialEvent(aEvent);
    }
    _partialSaved = partial;
}

void PandaXPMTDM::resetData() {
    killerProcess.clear();
    prekillerProcess.clear();
    lastTouchableVolume.clear();
    lastStepPreVol.clear();
    lastStepPostVol.clear();
    lastStepLength.clear();
    lastStepEdep.clear();
    opBoundStatus.clear();

    if (_recordPMT) 
    {
		_nPMTHits = 0;
        PMTSet.clear();
		_fPmtNumber.clear();
		_fPhotons.clear();
		_fPosX.clear();
		_fPosY.clear();
		_fPosZ.clear();
		_fTimeGlo.clear();
		_fTimeLoc.clear();
		_fTimePro.clear();
		//_fTimeDet.clear();
		_fTrackID.clear();
		_trackMap.clear();
	}
	
	//if (_recordPrimaryParticle)
	{
        _nPrimaries = 0;
        _primaryType.clear();
        _primaryId.clear();
        _primaryEnergy.clear();
        _primaryPx.clear();
        _primaryPy.clear();
        _primaryPz.clear();
        _primaryX.clear();
        _primaryY.clear();
        _primaryZ.clear();
        _primaryT.clear();
    }

}

void PandaXPMTDM::resetPartialEvent(const G4Event *aEvent) {
    G4HCofThisEvent *hCthis = aEvent->GetHCofThisEvent();
    int nHitCollections = hCthis->GetNumberOfCollections();
    for (int i = 0; i < nHitCollections; ++i) 
    {
        G4VHitsCollection *hitsCollection = hCthis->GetHC(i);
		if (hitsCollection->GetName().contains("pmtHitCollection")) 
		{
            auto hC = (PandaXPMTHitsCollection *)hitsCollection;
            for (int j = 0; j < hC->entries(); ++j) 
            {
                delete (*hC)[j];
            }
            hC->GetVector()->clear();
        } 
    }
}

std::map<int, std::string> &PandaXPMTDM::getTrackMap() {
    return _trackMap;
}

PandaXPMTDM *PandaXPMTDM::Instance() {
    if (_instance == 0) {
        return new PandaXPMTDM();
    }
    return _instance;
}

void PandaXPMTDM::addTemporaryPMTParticle(const TemporaryPMTParticle &tp) {
    _tparticles.push_back(tp);
}
