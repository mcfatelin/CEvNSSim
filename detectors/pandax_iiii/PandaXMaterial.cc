#include "PandaXMaterial.hh"
#include "detector/BambooMaterialFactory.hh"
#include "BambooGlobalVariables.hh"

#include <G4Material.hh>
#include <G4NistManager.hh>

#include <vector>

#include <G4OpticalSurface.hh>

//#define NO_ABSLENGTH	// Pick
//#define NO_ABSLENGTH_MESH	// Mesh & Grid
//#define NO_RAYLEIGH		// Pick
//#define NO_FRESNEL		// Pick
// NO_FRESNEL will change the RINDEX of all kind of LXe to be
// the same as GXe, which is 1.00
// NO_FRESNEL will used to the two situations:
// 1. when wanted to estimate/test the transparency of mesh layers
// 2. when wanted to simulate NO_OPTICAL mode for calculating the solid angle

using std::vector;
// anonymous namespace to register the PandaXMaterial

MaterialRegister<PandaXMaterial> PandaXMaterial::reg("PandaXMaterial");

// transparency values are evaluated from MC
const G4double PandaXMaterial::c_abs_len_gxe = 100.*m;
const G4double PandaXMaterial::c_abs_len_gxe_mesh = 0.1255*cm;	// for 86% transparency

const G4double PandaXMaterial::c_abs_len_lxe = 10.*m;
const G4double PandaXMaterial::c_abs_len_lxe_mesh = 0.134*cm;	// for 86% transparency
const G4double PandaXMaterial::c_abs_len_lxe_grid = 0.35*cm;	// for 94% transparency

/*
namespace {

  BambooMaterial * createPandaXMaterial ()
  {
    return new PandaXMaterial("PandaXMaterial");
  }

  const std::string PandaXMaterialName("PandaXMaterial");

  const bool registered = BambooMaterialFactory::Instance()->registerMaterial(PandaXMaterialName, createPandaXMaterial);
}
*/

PandaXMaterial::PandaXMaterial (const G4String & name)
  : BambooMaterial(name)
{
  G4cout << "PandaXMaterial found..." << G4endl;
}


void PandaXMaterial::defineMaterials()
{
  G4NistManager * pNistManager = G4NistManager::Instance();

  vector<G4Element *> elementVec;
  vector<G4Material *> materialVec;
  G4Element * H = pNistManager->FindOrBuildElement(1);  elementVec.push_back(H);
  G4Element * Be = pNistManager->FindOrBuildElement(5);  elementVec.push_back(Be);
  G4Element * C = pNistManager->FindOrBuildElement(6);  elementVec.push_back(C);
  G4Element * N = pNistManager->FindOrBuildElement(7);  elementVec.push_back(N);
  G4Element * O = pNistManager->FindOrBuildElement(8);  elementVec.push_back(O);
  G4Element * F = pNistManager->FindOrBuildElement(9);  elementVec.push_back(F);
  G4Element * Mg = pNistManager->FindOrBuildElement(12);  elementVec.push_back(Mg);
  G4Element * Al = pNistManager->FindOrBuildElement(13);  elementVec.push_back(Al);
  G4Element * Si = pNistManager->FindOrBuildElement(14);  elementVec.push_back(Si);
  G4Element * P = pNistManager->FindOrBuildElement(15);  elementVec.push_back(P);
  G4Element * S = pNistManager->FindOrBuildElement(16);  elementVec.push_back(S);
  G4Element * Cl = pNistManager->FindOrBuildElement(17);  elementVec.push_back(Cl);
  G4Element * K = pNistManager->FindOrBuildElement(19);  elementVec.push_back(K);
  G4Element * Ca = pNistManager->FindOrBuildElement(20);  elementVec.push_back(Ca);
  G4Element * Cr = pNistManager->FindOrBuildElement(24);  elementVec.push_back(Cr);
  G4Element * Mn = pNistManager->FindOrBuildElement(25);  elementVec.push_back(Mn);
  G4Element * Fe = pNistManager->FindOrBuildElement(26);  elementVec.push_back(Fe);
  G4Element * Ni = pNistManager->FindOrBuildElement(28);  elementVec.push_back(Ni);
  G4Element * Cu = pNistManager->FindOrBuildElement(29);  elementVec.push_back(Cu);
  G4Element * Pb = pNistManager->FindOrBuildElement(82);  elementVec.push_back(Pb);
  G4Element * Sn = pNistManager->FindOrBuildElement(50);  elementVec.push_back(Sn);
  //G4Element* B = pNistManager->FindOrBuildElement("B");
  //G4Element* Gd = pNistManager->FindOrBuildElement("Gd");
  G4Element *Xe = new G4Element("Xenon",     "Xe", 54., 131.293*g/mole); elementVec.push_back(Xe);
  G4Element *Ti = new G4Element("Ti",        "Ti", 22., 47.867*g/mole); elementVec.push_back(Ti);
  G4Element *Na = new G4Element("Na",        "Na", 11., 22.989769*g/mole); elementVec.push_back(Na);
  G4cout << "Avaliable elements: " << G4endl;
  for (size_t i=0; i<elementVec.size(); ++i) {G4cout << elementVec[i]->GetName() << " ";}
  G4cout << G4endl;
  G4Material * concrete = pNistManager->FindOrBuildMaterial("G4_CONCRETE");
  materialVec.push_back(concrete);
  G4Material * marble = new G4Material("MARBLE", 2.71*g/cm3, 7, kStateSolid);
  marble->AddElement( C, 11.88 * 0.01);
  marble->AddElement( O, 47.91 * 0.01);
  marble->AddElement(Mg, 5.58 * 0.01);
  marble->AddElement(Al, 1.535 * 0.01);
  marble->AddElement(Si, 1.27 * 0.01);
  marble->AddElement( K, 1.535 * 0.01);
  marble->AddElement(Ca, 30.29 * 0.01);
  materialVec.push_back(marble);
  G4Material * air = pNistManager->FindOrBuildMaterial("G4_AIR");
  materialVec.push_back(air);

  G4cout << "Available materials: " << G4endl;
  for (size_t i=0; i<materialVec.size(); ++i) {G4cout << materialVec[i]->GetName() << " ";}
  G4cout << G4endl;

  //---------- polyethylene ----------//
  G4Material *Polyethylene = new G4Material("Polyethylene", 0.94*g/cm3, 2, kStateSolid);
  Polyethylene->AddElement(C, 2);
  Polyethylene->AddElement(H, 4);

  //---------- Be-doped polyethylene -------------//
  G4Material *BeDopedPolyethylene       = new G4Material("BeDopedPolyethylene", 0.94*g/cm3, 3, kStateSolid);
  BeDopedPolyethylene->AddElement(C, 10);
  BeDopedPolyethylene->AddElement(H, 20);
  BeDopedPolyethylene->AddElement(Be, 3); // 10% Be doping

  //----------- Air --------------------//
  G4Material *Air                       = new G4Material("Air",1.2929*kg/m3, 2, kStateGas, 300.00*kelvin, 1.0*atmosphere);
  Air->AddElement(N, 0.8);
  Air->AddElement(O , 0.2);
	
  //---------- Lead ----------//
  G4Material *Lead = new G4Material("Lead", 11.34*g/cm3, 1);
  Lead->AddElement(Pb, 1); 

  //---------- shielding copper (no reflectivity) ----------//
  G4Material *ShieldingCopper = new G4Material("ShieldingCopper", 8.92*g/cm3, 1);
  ShieldingCopper->AddElement(Cu, 1); 

  //---------- air ----------//
  pNistManager->FindOrBuildMaterial("G4_AIR");

  //---------- vacuum ----------//
  G4Material *Vacuum = new G4Material("Vacuum", 1.e-20*g/cm3, 2, kStateGas);
  Vacuum->AddElement(N, 0.755);
  Vacuum->AddElement(O, 0.245);

  //---------- water ----------//
  G4Material *Water = new G4Material("Water", 1.*g/cm3, 2, kStateLiquid);
  Water->AddElement(H, 2);
  Water->AddElement(O, 1);

  pNistManager->FindOrBuildMaterial("G4_AIR");

  G4Material * water = pNistManager->FindOrBuildMaterial("G4_WATER");
  materialVec.push_back(water);

  //---------- liquid scintillator (Borexino) ----------//
  G4Material* PC = new G4Material("PC", 0.882*g/cm3, 2, kStateLiquid);
  PC->AddElement(C, 9);
  PC->AddElement(H, 12);

  G4Material* PPO = new G4Material("PPO", 0.882*g/cm3, 4, kStateSolid);
  PPO->AddElement(C, 15);
  PPO->AddElement(H, 11);
  PPO->AddElement(N, 1);
  PPO->AddElement(O, 1);

  G4Material* LScint = new G4Material("LScint", 0.882*g/cm3, 2, kStateLiquid);
  LScint->AddMaterial(PC, 0.9983);
  LScint->AddMaterial(PPO, 0.0017);

  //---------- liquid xenon ----------
  G4Material *LXe = new G4Material("LXe", 2.85*g/cm3, 1, kStateLiquid, 168.15*kelvin, 1.5*atmosphere);
  LXe->AddElement(Xe, 1);

  const G4int iNbEntries = 3;

  G4double pdLXePhotonMomentum[iNbEntries]   = {6.91*eV, 6.98*eV, 7.05*eV};
  G4double pdLXeScintillation[iNbEntries]    = {0.1,     1.0,     0.1};

#ifdef NO_FRESNEL
  G4double pdLXeRefractiveIndex[iNbEntries]  = {1.00,    1.00,    1.00};
#else
  G4double pdLXeRefractiveIndex[iNbEntries]  = {1.63,    1.61,    1.58};
#endif
#ifndef NO_ABSLENGTH
  G4double pdLXeAbsorbtionLength[iNbEntries] = {c_abs_len_lxe, c_abs_len_lxe, c_abs_len_lxe};
#endif
#ifndef NO_RAYLEIGH
  G4double pdLXeScatteringLength[iNbEntries] = {50.*cm,  50.*cm,  50.*cm};
#endif

  G4MaterialPropertiesTable *pLXePropertiesTable = new G4MaterialPropertiesTable();
	
  pLXePropertiesTable->AddProperty("FASTCOMPONENT", pdLXePhotonMomentum, pdLXeScintillation, iNbEntries);
  pLXePropertiesTable->AddProperty("SLOWCOMPONENT", pdLXePhotonMomentum, pdLXeScintillation, iNbEntries);
  pLXePropertiesTable->AddProperty("RINDEX", pdLXePhotonMomentum, pdLXeRefractiveIndex, iNbEntries);
#ifndef NO_ABSLENGTH
  pLXePropertiesTable->AddProperty("ABSLENGTH", pdLXePhotonMomentum, pdLXeAbsorbtionLength, iNbEntries);
#endif
#ifndef NO_RAYLEIGH
  pLXePropertiesTable->AddProperty("RAYLEIGH", pdLXePhotonMomentum, pdLXeScatteringLength, iNbEntries);
#endif
	
  pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0./keV);
  pLXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
  pLXePropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3.*ns);
  pLXePropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27.*ns);
  pLXePropertiesTable->AddConstProperty("YIELDRATIO", 1.0);
	
  LXe->SetMaterialPropertiesTable(pLXePropertiesTable);

  //-------------------------------- gaseous xenon --------------------------------
  G4Material *GXe = new G4Material("GXe", 0.005887*g/cm3, 1, kStateGas, 173.15*kelvin, 1.5*atmosphere);
  GXe->AddElement(Xe, 1);

  G4double pdGXePhotonMomentum[iNbEntries]   = {6.91*eV, 6.98*eV, 7.05*eV};
  G4double pdGXeScintillation[iNbEntries]    = {0.1,     1.0,     0.1};
  G4double pdGXeRefractiveIndex[iNbEntries]  = {1.00,    1.00,    1.00};
#ifndef NO_ABSLENGTH
  G4double pdGXeAbsorbtionLength[iNbEntries] = {c_abs_len_gxe,   c_abs_len_gxe,   c_abs_len_gxe};
#endif
#ifndef NO_RAYLEIGH
  G4double pdGXeScatteringLength[iNbEntries] = {100*m,   100*m,   100*m};
#endif

  G4MaterialPropertiesTable *pGXePropertiesTable = new G4MaterialPropertiesTable();

  pGXePropertiesTable->AddProperty("FASTCOMPONENT", pdGXePhotonMomentum, pdGXeScintillation, iNbEntries);
  pGXePropertiesTable->AddProperty("SLOWCOMPONENT", pdGXePhotonMomentum, pdGXeScintillation, iNbEntries);
  pGXePropertiesTable->AddProperty("RINDEX", pdGXePhotonMomentum, pdGXeRefractiveIndex, iNbEntries);
#ifndef NO_ABSLENGTH
  pGXePropertiesTable->AddProperty("ABSLENGTH", pdGXePhotonMomentum, pdGXeAbsorbtionLength, iNbEntries);
#endif
#ifndef NO_RAYLEIGH
  pGXePropertiesTable->AddProperty("RAYLEIGH", pdGXePhotonMomentum, pdGXeScatteringLength, iNbEntries);
#endif

  pGXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0./(keV));
  pGXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
  pGXePropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3.*ns);
  pGXePropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27.*ns);
  pGXePropertiesTable->AddConstProperty("YIELDRATIO", 1.0);

  GXe->SetMaterialPropertiesTable(pGXePropertiesTable);	

  //----------------------------------- quartz ------------------------------------
  // ref: http://www.sciner.com/Opticsland/FS.htm
  G4Material *Quartz = new G4Material("Quartz", 2.201*g/cm3, 2, kStateSolid, 168.15*kelvin, 1.5*atmosphere);
  Quartz->AddElement(Si, 1);
  Quartz->AddElement(O, 2);

  G4double pdQuartzPhotonMomentum[iNbEntries]   = {6.91*eV, 6.98*eV, 7.05*eV};
  G4double pdQuartzRefractiveIndex[iNbEntries]  = {1.50,    1.56,    1.60};
  G4double pdQuartzAbsorbtionLength[iNbEntries] = {30*m,    30*m,    30*m};

  G4MaterialPropertiesTable *pQuartzPropertiesTable = new G4MaterialPropertiesTable();

  pQuartzPropertiesTable->AddProperty("RINDEX", pdQuartzPhotonMomentum, pdQuartzRefractiveIndex, iNbEntries);
  pQuartzPropertiesTable->AddProperty("ABSLENGTH", pdQuartzPhotonMomentum, pdQuartzAbsorbtionLength, iNbEntries);

  Quartz->SetMaterialPropertiesTable(pQuartzPropertiesTable);

  //------------------------------- stainless steel -------------------------------
  {
	  G4Material *SS304LSteel = new G4Material("SS304LSteel", 8.00*g/cm3, 5, kStateSolid);
	  SS304LSteel->AddElement(Fe, 0.65);
	  SS304LSteel->AddElement(Cr, 0.20);
	  SS304LSteel->AddElement(Ni, 0.12);
	  SS304LSteel->AddElement(Mn, 0.02);
	  SS304LSteel->AddElement(Si, 0.01);
	  //debug 1
	  G4double pdSteelPhotonMomentum[] = {6.91*eV, 6.98*eV, 7.05*eV};
	  G4double pdSteelReflectivity[]   = {0.15,    0.2,     0.15};
	  G4double pdSteelEfficiency[]     = {  0.,      0.,       0.};	//#Pick
	  G4MaterialPropertiesTable *pSteelPropertiesTable = new G4MaterialPropertiesTable();

	  pSteelPropertiesTable->AddProperty("REFLECTIVITY", pdSteelPhotonMomentum, pdSteelReflectivity, iNbEntries);
	  pSteelPropertiesTable->AddProperty("EFFICIENCY", pdSteelPhotonMomentum, pdSteelEfficiency, iNbEntries);	//#Pick
	  SS304LSteel->SetMaterialPropertiesTable(pSteelPropertiesTable);
	  //debug 2
  }

	vector<G4double> photon_momentum = {6.91*eV, 6.98*eV, 7.05*eV};
  
	//------------------------------- GXE FOR MESH ------------------------------- //#Pick
	{
		G4Material *GXeMesh = new G4Material("GXE_MESH", 0.005887*g/cm3, 1, kStateGas, 173.15*kelvin, 1.5*atmosphere);
		GXeMesh->AddElement(Xe, 1);

		G4MaterialPropertiesTable *pt_ = new G4MaterialPropertiesTable();
		pt_->AddProperty("FASTCOMPONENT", photon_momentum.data(), vector<G4double>{0.1, 1.0, 0.1}.data(), photon_momentum.size());
		pt_->AddProperty("SLOWCOMPONENT", photon_momentum.data(), vector<G4double>{0.1, 1.0, 0.1}.data(), photon_momentum.size());
		pt_->AddProperty("RINDEX", photon_momentum.data(), vector<G4double>{1., 1., 1.}.data(), photon_momentum.size());
#ifndef NO_ABSLENGTH_MESH
		pt_->AddProperty("ABSLENGTH", photon_momentum.data(), vector<G4double>{c_abs_len_gxe_mesh, c_abs_len_gxe_mesh, c_abs_len_gxe_mesh}.data(), photon_momentum.size());
#endif
		//#ifndef NO_RAYLEIGH
		//pt_->AddProperty("RAYLEIGH", photon_momentum.data(), vector<G4double>{100.*cm, 100.*cm, 100.*cm}.data(), photon_momentum.size());
		//#endif

		//pt_->AddProperty("REFLECTIVITY", photon_momentum.data(), vector<G4double>{0, 0, 0}.data(), photon_momentum.size());
		//pt_->AddProperty("EFFICIENCY", photon_momentum.data(), vector<G4double>{0.86, 0.86, 0.86}.data(), photon_momentum.size());

		//pt_->AddConstProperty("SCINTILLATIONYIELD", 0./(keV));
		//pt_->AddConstProperty("RESOLUTIONSCALE", 0);
		//pt_->AddConstProperty("FASTTIMECONSTANT", 3.*ns);
		//pt_->AddConstProperty("SLOWTIMECONSTANT", 27.*ns);
		//pt_->AddConstProperty("YIELDRATIO", 1.0);

		GXeMesh->SetMaterialPropertiesTable(pt_);	
	}

	//------------------------------- LXE FOR MESH ------------------------------- //#Pick
	{
		auto LXeMesh = new G4Material("LXE_MESH", 2.85*g/cm3, 1, kStateLiquid, 168.15*kelvin, 1.5*atmosphere);
		LXeMesh->AddElement(Xe, 1);

		auto pt_ = new G4MaterialPropertiesTable();
		pt_->AddProperty("FASTCOMPONENT", photon_momentum.data(), vector<G4double>{0.1, 1.0, 0.1}.data(), photon_momentum.size());
		pt_->AddProperty("SLOWCOMPONENT", photon_momentum.data(), vector<G4double>{0.1, 1.0, 0.1}.data(), photon_momentum.size());
#ifdef NO_FRESNEL
		pt_->AddProperty("RINDEX", photon_momentum.data(), vector<G4double>{1.00, 1.00, 1.00}.data(), photon_momentum.size());
#else
		pt_->AddProperty("RINDEX", photon_momentum.data(), vector<G4double>{1.63, 1.61, 1.58}.data(), photon_momentum.size());
#endif
#ifndef NO_ABSLENGTH_MESH
		pt_->AddProperty("ABSLENGTH", photon_momentum.data(), vector<G4double>{c_abs_len_lxe_mesh, c_abs_len_lxe_mesh, c_abs_len_lxe_mesh}.data(), photon_momentum.size());
#endif
		//pt_->AddProperty("ABSLENGTH", photon_momentum.data(), vector<G4double>{0.01*mm, 0.01*cm, 0.01*cm}.data(), photon_momentum.size());
		//#ifndef NO_RAYLEIGH
		//pt_->AddProperty("RAYLEIGH", photon_momentum.data(), vector<G4double>{50.*cm, 50.*cm, 50.*cm}.data(), photon_momentum.size());
		//#endif

		//pt_->AddProperty("REFLECTIVITY", photon_momentum.data(), vector<G4double>{0, 0, 0}.data(), photon_momentum.size());
		//pt_->AddProperty("EFFICIENCY", photon_momentum.data(), vector<G4double>{0.86, 0.86, 0.86}.data(), photon_momentum.size());

		//pt_->AddConstProperty("SCINTILLATIONYIELD", 0./keV);
		//pt_->AddConstProperty("RESOLUTIONSCALE", 0);
		//pt_->AddConstProperty("FASTTIMECONSTANT", 3.*ns);
		//pt_->AddConstProperty("SLOWTIMECONSTANT", 27.*ns);
		//pt_->AddConstProperty("YIELDRATIO", 1.0);

		LXeMesh->SetMaterialPropertiesTable(pt_);
	}

	//------------------------------- LXE FOR GRID ------------------------------- //#Pick
	{
		auto LXeGrid = new G4Material("LXE_GRID", 2.85*g/cm3, 1, kStateLiquid, 168.15*kelvin, 1.5*atmosphere);
		LXeGrid->AddElement(Xe, 1);
		
//		vector<G4double> photon_momentum = {6.91*eV, 6.98*eV, 7.05*eV};

		auto pt_ = new G4MaterialPropertiesTable();
		pt_->AddProperty("FASTCOMPONENT", photon_momentum.data(), vector<G4double>{0.1, 1.0, 0.1}.data(), photon_momentum.size());
		pt_->AddProperty("SLOWCOMPONENT", photon_momentum.data(), vector<G4double>{0.1, 1.0, 0.1}.data(), photon_momentum.size());
#ifdef NO_FRESNEL
		pt_->AddProperty("RINDEX", photon_momentum.data(), vector<G4double>{1.00, 1.00, 1.00}.data(), photon_momentum.size());
#else
		pt_->AddProperty("RINDEX", photon_momentum.data(), vector<G4double>{1.63, 1.61, 1.58}.data(), photon_momentum.size());
#endif
#ifndef NO_ABSLENGTH_MESH
		pt_->AddProperty("ABSLENGTH", photon_momentum.data(), vector<G4double>{c_abs_len_lxe_grid, c_abs_len_lxe_grid, c_abs_len_lxe_grid}.data(), photon_momentum.size());
#endif
		//#ifndef NO_RAYLEIGH
		//pt_->AddProperty("RAYLEIGH", photon_momentum.data(), vector<G4double>{50.*cm, 50.*cm, 50.*cm}.data(), photon_momentum.size());
		//#endif

		//pt_->AddProperty("REFLECTIVITY", photon_momentum.data(), vector<G4double>{0, 0, 0}.data(), photon_momentum.size());
		//pt_->AddProperty("EFFICIENCY", photon_momentum.data(), vector<G4double>{0.94, 0.94, 0.94}.data(), photon_momentum.size());

		//pt_->AddConstProperty("SCINTILLATIONYIELD", 0./keV);
		//pt_->AddConstProperty("RESOLUTIONSCALE", 0);
		//pt_->AddConstProperty("FASTTIMECONSTANT", 3.*ns);
		//pt_->AddConstProperty("SLOWTIMECONSTANT", 27.*ns);
		//pt_->AddConstProperty("YIELDRATIO", 1.0);

		LXeGrid->SetMaterialPropertiesTable(pt_);
	}

  //---------------------------------- titanium ----------------------------------
  //G4Material *Titanium = pNistManager->FindOrBuildMaterial("G4_Ti");
  pNistManager->FindOrBuildMaterial("G4_Ti");

  //---------------------------- photocathode aluminium ---------------------------
  G4Material *PhotoCathodeAluminium = new G4Material("PhotoCathodeAluminium", 8.00*g/cm3, 1, kStateSolid);
  PhotoCathodeAluminium->AddElement(Al, 1);

  G4double pdPhotoCathodePhotonMomentum[]   = {6.91*eV, 6.98*eV, 7.05*eV};
  G4double pdPhotoCathodeRefractiveIndex[]  = {1.50,    1.56,    1.60};
  G4double pdPhotoCathodeAbsorbtionLength[] = {1.*nm,   1.*nm,   1.*nm};
  G4MaterialPropertiesTable *pPhotoCathodePropertiesTable = new G4MaterialPropertiesTable();

  pPhotoCathodePropertiesTable->AddProperty("RINDEX", pdPhotoCathodePhotonMomentum, pdPhotoCathodeRefractiveIndex, iNbEntries);
  pPhotoCathodePropertiesTable->AddProperty("ABSLENGTH", pdPhotoCathodePhotonMomentum, pdPhotoCathodeAbsorbtionLength, iNbEntries);

  PhotoCathodeAluminium->SetMaterialPropertiesTable(pPhotoCathodePropertiesTable);

  //---------------------------- QUPID aluminium coating---------------------------
  G4Material *CoatingAluminium = new G4Material("CoatingAluminium", 2.7*g/cm3, 1, kStateSolid);
  CoatingAluminium->AddElement(Al, 1);

  G4double pdCoatingAluminiumPhotonMomentum[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
  G4double pdCoatingAluminiumReflectivity[iNbEntries]   = {0.15,    0.2,     0.15};/// check
  G4MaterialPropertiesTable *pCoatingAluminiumPropertiesTable = new G4MaterialPropertiesTable();

  pCoatingAluminiumPropertiesTable->AddProperty("REFLECTIVITY", pdCoatingAluminiumPhotonMomentum, pdCoatingAluminiumReflectivity, iNbEntries);
  CoatingAluminium->SetMaterialPropertiesTable(pCoatingAluminiumPropertiesTable);

  //----------------------------- grid mesh aluminium------------------------------
  G4Material *GridMeshAluminium = new G4Material("GridMeshAluminium", 0.174*g/cm3, 1, kStateSolid);
  GridMeshAluminium->AddElement(Al, 1);
	
  G4double pdGridMeshPhotonMomentum[] = {6.91*eV, 6.98*eV, 7.05*eV};
  G4double *pdGridMeshRefractiveIndex = pdLXeRefractiveIndex;
  G4double dAbsortionLength = 2.10*mm; // exp(-GridMeshThickness/2.10) = 0.94
  G4double pdGridMeshAbsortionLength[] = {dAbsortionLength, dAbsortionLength, dAbsortionLength};
	
  G4MaterialPropertiesTable *pGridMeshPropertiesTable = new G4MaterialPropertiesTable();

  pGridMeshPropertiesTable->AddProperty("RINDEX", pdGridMeshPhotonMomentum, pdGridMeshRefractiveIndex, iNbEntries);
  pGridMeshPropertiesTable->AddProperty("ABSLENGTH", pdGridMeshPhotonMomentum, pdGridMeshAbsortionLength, iNbEntries);
  GridMeshAluminium->SetMaterialPropertiesTable(pGridMeshPropertiesTable);

  //------------------------------------ teflon -----------------------------------
  G4Material* Teflon = new G4Material("Teflon", 2.2*g/cm3, 2, kStateSolid);
  Teflon->AddElement(C, 0.240183);
  Teflon->AddElement(F, 0.759817);

  G4double pdTeflonPhotonMomentum[iNbEntries]  = {6.91*eV, 6.98*eV, 7.05*eV};
  G4double pdTeflonRefractiveIndex[iNbEntries] = {1.63,    1.61,    1.58}; //#Pick: Should teflon having refraction index?
  //G4double pdTeflonReflectivity[iNbEntries]    = {0.95,    0.95,    0.95}; //#Pick
  G4double pdTeflonReflectivity[iNbEntries] = { 0.99,    0.99,    0.99 }; //GG
  //G4double pdTeflonReflectivity[iNbEntries]    = {0.0,     0.0,     0.0};	//#Pick
  G4double pdTeflonSpecularLobe[iNbEntries]    = {0.01,    0.01,    0.01};
  G4double pdTeflonSpecularSpike[iNbEntries]   = {0.01,    0.01,    0.01};
  G4double pdTeflonBackscatter[iNbEntries]     = {0.01,    0.01,    0.01};
  //G4double pdTeflonEfficiency[iNbEntries]      = {1.0,     1.0,     1.0};	//#Pick
  G4double pdTeflonEfficiency[iNbEntries]      = {0.0,     0.0,     0.0};	//#Pick
  auto *pTeflonPropertiesTable = new G4MaterialPropertiesTable();

  pTeflonPropertiesTable->AddProperty("RINDEX", pdTeflonPhotonMomentum, pdTeflonRefractiveIndex, iNbEntries);
  pTeflonPropertiesTable->AddProperty("REFLECTIVITY", pdTeflonPhotonMomentum, pdTeflonReflectivity, iNbEntries);
  pTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT", pdTeflonPhotonMomentum, pdTeflonSpecularLobe, iNbEntries);
  pTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT", pdTeflonPhotonMomentum, pdTeflonSpecularSpike, iNbEntries);
  pTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT", pdTeflonPhotonMomentum, pdTeflonBackscatter, iNbEntries);
  pTeflonPropertiesTable->AddProperty("EFFICIENCY", pdTeflonPhotonMomentum, pdTeflonEfficiency, iNbEntries);
  Teflon->SetMaterialPropertiesTable(pTeflonPropertiesTable);

  
  //------------------------------------ copper -----------------------------------
  G4Material *Copper = new G4Material("Copper", 8.92*g/cm3, 1);
  Copper->AddElement(Cu, 1); 

  G4double pdCopperPhotonMomentum[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
  G4double pdCopperReflectivity[iNbEntries]   = {0.15,    0.2,     0.15};
  G4MaterialPropertiesTable *pCopperPropertiesTable = new G4MaterialPropertiesTable();

  pCopperPropertiesTable->AddProperty("REFLECTIVITY", pdCopperPhotonMomentum, pdCopperReflectivity, iNbEntries);
  Copper->SetMaterialPropertiesTable(pCopperPropertiesTable);

 
  //------------------------------------ceramic-------------------------------------------
  
  G4Material * Ceramic = new G4Material("Ceramic", 2.88*g/cm3, 2);
  Ceramic->AddElement( Al, 2);
  Ceramic->AddElement( O, 3);
 // Ceramic->SetMaterialPropertiesTable(pCeramicPropertiesTable);


  //------------------------------------cirlex-------------------------------------------
  G4Material *Cirlex = new G4Material("Cirlex", 1.43*g/cm3, 4, kStateSolid);
  Cirlex->AddElement(C, 22);
  Cirlex->AddElement(H, 10);
  Cirlex->AddElement(N, 2);
  Cirlex->AddElement(O, 5);
  
  //------------------------------------ marble ------------------------------------
  G4Material* Marble = new G4Material("Marble", 2.71*g/cm3, 7, kStateSolid);  	
  Marble->AddElement( C, 11.88 * 0.01);
  Marble->AddElement( O, 47.91 * 0.01);
  Marble->AddElement(Mg, 5.58 * 0.01);
  Marble->AddElement(Al, 1.535 * 0.01);
  Marble->AddElement(Si, 1.27 * 0.01);
  Marble->AddElement( K, 1.535 * 0.01);
  Marble->AddElement(Ca, 30.29 * 0.01);
  //--------------------------------------concrete------------------------------------
  G4Material *    Concrete = new G4Material ("Concrete", 2.4 * g / cm3, 13);
  Concrete->AddElement( H, 0.89 * 0.01);
  Concrete->AddElement( C, 7.99 * 0.01);
  Concrete->AddElement( O, 48.43 * 0.01);
  Concrete->AddElement( Na, 0.6 * 0.01);
  Concrete->AddElement(Mg, 0.85 * 0.01);
  Concrete->AddElement(Al, 0.9 * 0.01);
  Concrete->AddElement(Si, 3.86 * 0.01);
  Concrete->AddElement(P, 0.04 * 0.01);
  Concrete->AddElement(S, 0.16 * 0.01);
  Concrete->AddElement( K, 0.54 * 0.01);
  Concrete->AddElement(Ca, 35.06 * 0.01);
  Concrete->AddElement(Ti, 0.04 * 0.01);
  Concrete->AddElement(Fe, 0.64 * 0.01);

  //----------------------------------- soldering tin -------------------------------
  G4Material *solder = new G4Material("solder",11.34*g/cm3,2);
  solder->AddElement(Sn, 0.6);
  solder->AddElement(Pb, 0.4);
  
  //#Pick: PMT WINDOWS MATERIAL AND OPTICAL SURFACE PROPERTY
  // (INSTEAD OF QUARTZ)
  	auto Bialkali = new G4Material("Bialkali", 4.28*g/cm3, 3);
	Bialkali->AddMaterial(pNistManager->FindOrBuildMaterial("G4_K"), 0.133);
	Bialkali->AddMaterial(pNistManager->FindOrBuildMaterial("G4_Cs"), 0.452);
	Bialkali->AddMaterial(pNistManager->FindOrBuildMaterial("G4_Sb"), 0.415); 
	{
		G4double NUM_PP[iNbEntries]  = {6.91*eV, 6.98*eV, 7.05*eV};
		G4double pmt_opt_surf_REF[iNbEntries] = {0., 0., 0.};
		G4double pmt_opt_surf_EFF[iNbEntries] = {1., 1., 1.};

		auto pmt_opmt_ = new G4MaterialPropertiesTable();
		pmt_opmt_->AddProperty("EFFICIENCY", NUM_PP, pmt_opt_surf_EFF, iNbEntries);
		pmt_opmt_->AddProperty("REFLECTIVITY", NUM_PP, pmt_opt_surf_REF, iNbEntries);
		Bialkali->SetMaterialPropertiesTable(pmt_opmt_);
	}
}



