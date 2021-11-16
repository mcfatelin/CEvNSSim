#include "XenonDetector.hh"
#include "BambooGlobalVariables.hh"
#include "analysis/PandaXSensitiveDetector.hh"
#include "detector/BambooDetectorFactory.hh"
#include "analysis/PandaXPMTSD.hh"

#define ADD_OPTICAL_PROPERTY 
// NO_OPTICAL shall be used with:
// - PandaxMaterial.cc{enabled NO_FRESNEL}
// - PandaxMaterial.cc{enabled NO_RAYLEIGH}
// - PandaxMaterial.cc{enabled NO_ABSLENGTH}

#define ADD_OPTICAL_PTFE
#define ADD_OPTICAL_PMT
#define ADD_OPTICAL_MESH
#define ADD_SENSITIVE_DETECTOR
//#define NO_MESH

//#define TEST_TRANSPARENCY 
// have to be used with PandaxMaterial.cc{disabled ADD_RAYLIEGH}

//enable when need to visual the geometry
//this will disabled the binary operatin for some "hole" in the "plate"
//#define DEBUG_GEOMETRY_VISUALIZATION

DetectorRegister<XenonDetector> XenonDetector::reg("XenonDetector");


XenonDetector::XenonDetector(const G4String& name)	: BambooDetectorPart(name){
	G4cout << "XenonDetector found..." << G4endl;
}

G4bool XenonDetector::construct()
{
	DefineGeometryParametersPandaXSP("PandaX-SP");

    // detector construction
    // optical surface definition is embeded
    ConstructTPC();
    ConstructPMTArrays();

#ifdef ADD_OPTICAL_PROPERTY
    DefineOpticalSurface();
#endif


    // print
    G4cout << "===>>> Finishing Constructing Single Phase Detector!" << G4endl;


	return true;
}

//========== Single Phase Detector Construction===========//

G4bool
XenonDetector::ConstructTPC()
{
   // G4cout <<" start constructing TPC "<<G4endl;
//tubs & boxes
    G4double pRMin;
    G4double pRMax;
    G4double pDx;
    G4double pDy;
    G4double pDz;
//    G4double pSPhi;
    G4double pDPhi;
    G4double pZoffset;
//polycone
//    G4double   phiStart;
//    G4double   phiTotal;
//    G4int      numZPlane;
//    G4double   zPlane[20];
//    G4double   rInner[20];
//    G4double   rOuter[20];

// Polydedra
//    G4int     numSide;
//    G4int     numZPlanes;
   // G4double  zPlane[20];
   // G4double  rInner[20];
   // G4double  rOuter[20];

//materials
//	G4Material *Teflon = G4Material::GetMaterial("Teflon");
	G4Material *Copper = G4Material::GetMaterial("Copper");
	G4Material *LXe = G4Material::GetMaterial("LXe");
	G4Material *Air             = G4Material::GetMaterial("Air");
//	G4Material *GXe = G4Material::GetMaterial("GXe");
//	G4Material *Peek = G4Material::GetMaterial("Peek");
    G4Material *StainlessSteel = G4Material::GetMaterial("SS304LSteel");
    G4Material *BeDopedPE       = G4Material::GetMaterial("BeDopedPolyethylene");
    G4Material *Lead            = G4Material::GetMaterial("Lead");

	//================================== attributes =================================
//	G4Colour hPTFEColor(0.2, 0.2, 1., 1.);
//	G4VisAttributes *pPTFEVisAtt = new G4VisAttributes(hPTFEColor);
//	pPTFEVisAtt->SetVisibility(true);


	G4Colour hCopperColor(0.835, 0.424, 0.059, 0.50);
	G4VisAttributes *pCopperVisAtt = new G4VisAttributes(hCopperColor);
	pCopperVisAtt->SetVisibility(true);


	G4Colour hLXeColor(1., 0 , 0 , 1.000);
	G4VisAttributes *pLXeVisAtt = new G4VisAttributes(hLXeColor);
	pLXeVisAtt->SetVisibility(true);
//
//
//	G4Colour hGXeColor(1., 0, 0, 0.500);
//	G4VisAttributes *pGXeVisAtt = new G4VisAttributes(hGXeColor);
//	pGXeVisAtt->SetVisibility(true);

	// SS Color
	G4Color hSSColor(1, 1.0, 1.0, 1.);
	G4VisAttributes *pSSVisAtt = new G4VisAttributes(hSSColor);
	pSSVisAtt -> SetVisibility(true);
	
	// PEColoer
	G4Color hPEColor(0.2, 0.2, 1., 1.);
	G4VisAttributes *pPEVisAtt  = new G4VisAttributes(hPEColor);
	pPEVisAtt->SetVisibility(true);
	
	// Lead Color
	G4Colour hLeadColor(0.059, 0.424, 0.800, 0.70);
	G4VisAttributes *pLeadVisAtt = new G4VisAttributes(hLeadColor);
	pLeadVisAtt->SetVisibility(true);



	//
//	G4double pLXeDz = GetGeometryParameter("TeflonBlockHeight") / 2.;


	m_pMotherLogicalVolume = parentPart_->getContainerLogicalVolume();

    /////////////////////////////////////////////////////
    // From outer to inner: Lead -> PE -> Copper -> Air -> SS vessel -> LXe
    //////////////////////////////////////////////////////

    // ===================== Lead box  =========================
    pDx                         = GetGeometryParameter("LeadWidth")/2.;
    pDy                         = GetGeometryParameter("LeadWidth")/2.;
    pDz                         = GetGeometryParameter("LeadHeight")/2.;
    
    G4Box *pLeadLayer           = new G4Box("pLeadLayer", pDx, pDy, pDz);
    m_pLeadLayerLogicalVolume   = new G4LogicalVolume(pLeadLayer, Lead, "LeadLayerVolume", 0, 0, 0);
    m_pLeadLayerPhysicalVolume  = new G4PVPlacement(0, G4ThreeVector(), m_pLeadLayerLogicalVolume, "LeadLayer", m_pMotherLogicalVolume, false, 0);
    
    // ===================== PE box =========================
    pDx                         = GetGeometryParameter("PEWidth")/2.;
    pDy                         = GetGeometryParameter("PEWidth")/2.;
    pDz                         = GetGeometryParameter("PEHeight")/2.;
    
    G4Box *pPELayer             = new G4Box("pPELayer", pDx, pDy, pDz);
    m_pPELayerLogicalVolume     = new G4LogicalVolume(pPELayer, BeDopedPE, "PELayerVolume", 0, 0, 0);
    m_pPELayerPhysicalVolume    = new G4PVPlacement(0, G4ThreeVector(), m_pPELayerLogicalVolume, "PELayer", m_pLeadLayerLogicalVolume, false, 0);
    
    // ===================== Copper box =========================
    pDx                         = GetGeometryParameter("CopperWidth")/2.;
    pDy                         = GetGeometryParameter("CopperWidth")/2.;
    pDz                         = GetGeometryParameter("CopperHeight")/2.;
    
    G4Box *pCopperLayer                 = new G4Box("pCopperLayer", pDx, pDy, pDz);
    m_pCopperLayerLogicalVolume         = new G4LogicalVolume(pCopperLayer, Copper, "CopperLayerVolume", 0, 0, 0);
    m_pCopperLayerPhysicalVolume        = new G4PVPlacement(0, G4ThreeVector(), m_pCopperLayerLogicalVolume, "CopperLayer", m_pPELayerLogicalVolume, false, 0);

    // ====================== Air box ==============================
    pDx                         = GetGeometryParameter("CavityWidth")/2.;
    pDy                         = GetGeometryParameter("CavityWidth")/2.;
    pDz                         = GetGeometryParameter("CavityHeight")/2.;
    
    G4Box *pAirLayer                 = new G4Box("pAirLayer", pDx, pDy, pDz);
    m_pAirLayerLogicalVolume         = new G4LogicalVolume(pAirLayer, Air, "AirLayerVolume", 0, 0, 0);
    m_pAirLayerPhysicalVolume        = new G4PVPlacement(0, G4ThreeVector(), m_pAirLayerLogicalVolume, "AirLayer", m_pCopperLayerLogicalVolume, false, 0);

    // ======================= SS vessel & top/bottom plate ======================
    // vessel
    pRMin                       = GetGeometryParameter("SSVesselRadius");
    pRMax                       = GetGeometryParameter("SSVesselRadius") + GetGeometryParameter("SSVesselThickness");
    pDz                         = GetGeometryParameter("SSVesselHeight")/2.;

    G4Tubs *pSSVessel           = new G4Tubs("pSSVessel", pRMin, pRMax, pDz, 0.0*deg, 360.0*deg);
	m_pSSVesselLogicalVolume    = new G4LogicalVolume(pSSVessel, StainlessSteel, "SSVesselVolume", 0, 0, 0);
	m_pSSVesselLogicalVolume->SetVisAttributes(pSSVisAtt);
	m_pSSVesselPhysicalVolume   = new G4PVPlacement(0, G4ThreeVector(), m_pSSVesselLogicalVolume, "SSVessel", m_pAirLayerLogicalVolume, false, 0);
	
	// top/bottom plate
	pRMin                       = 0.0*mm;
	pRMax                       = GetGeometryParameter("SSVesselRadius") + GetGeometryParameter("SSVesselThickness");
	pDz                         = GetGeometryParameter("SSVesselThickness")/2.;
	G4double pOffsetZ           = GetGeometryParameter("SSVesselHeight")/2.+GetGeometryParameter("SSVesselThickness")/2.;
	
	G4Tubs *pSSTop              = new G4Tubs("pSSTop", pRMin, pRMax, pDz, 0.0*deg, 360.0*deg);
	m_pSSTopLogicalVolume       = new G4LogicalVolume(pSSTop, StainlessSteel, "SSTopVolume", 0,0,0);
	m_pSSTopLogicalVolume->SetVisAttributes(pSSVisAtt);
	m_pSSTopPhysicalVolume      = new G4PVPlacement(0, G4ThreeVector(0,0,pOffsetZ), m_pSSTopLogicalVolume, "SSTop", m_pAirLayerLogicalVolume, false, 0);
	
	G4Tubs *pSSBottom              = new G4Tubs("pSSBottom", pRMin, pRMax, pDz, 0.0*deg, 360.0*deg);
	m_pSSBottomLogicalVolume       = new G4LogicalVolume(pSSBottom, StainlessSteel, "SSBottomVolume", 0,0,0);
	m_pSSBottomLogicalVolume->SetVisAttributes(pSSVisAtt);
	m_pSSBottomPhysicalVolume      = new G4PVPlacement(0, G4ThreeVector(0,0,-pOffsetZ), m_pSSBottomLogicalVolume, "SSBottom", m_pAirLayerLogicalVolume, false, 0);

	// ========================= LXe =============================
	pRMin                       = 0.0*mm;
	pRMax                       = GetGeometryParameter("LXeRadius");
	pDz                         = GetGeometryParameter("LXeHeight")/2.;

	// debug
	G4cout<<"LXe radius = "<<pRMax/mm<<G4endl;

	G4Tubs  *pLXe               = new G4Tubs("pLXe", pRMin, pRMax, pDz, 0.0*deg, 360.0*deg);
	m_pLXeLogicalVolume         = new G4LogicalVolume(pLXe, LXe, "LXeVolume", 0, 0, 0);
	m_pLXeLogicalVolume->SetVisAttributes(pLXeVisAtt);
	m_pLXePhysicalVolume        = new G4PVPlacement(0, G4ThreeVector(), m_pLXeLogicalVolume, "LXe", m_pAirLayerLogicalVolume, false, 0);
	


    // ================== set sensitive volume ====================
	G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
//	PandaXSensitiveDetector *ppLXeSD    = new PandaXSensitiveDetector("LXeSD", true, true);
	PandaXSensitiveDetector *ppLXeSD    = new PandaXSensitiveDetector("LXeSD", true, false); // just deposition
	pSDManager->AddNewDetector(ppLXeSD);
	m_pLXeLogicalVolume->SetSensitiveDetector(ppLXeSD);
	// other volumes
//	m_pSSTopLogicalVolume->SetSensitiveDetector(ppLXeSD);
//	m_pSSBottomLogicalVolume->SetSensitiveDetector(ppLXeSD);
//	m_pSSVesselLogicalVolume->SetSensitiveDetector(ppLXeSD);
//	m_pCopperLayerLogicalVolume->SetSensitiveDetector(ppLXeSD);
//	m_pPELayerLogicalVolume->SetSensitiveDetector(ppLXeSD);
//	m_pLeadLayerLogicalVolume->SetSensitiveDetector(ppLXeSD);


    auto neutronFilter = new G4SDParticleFilter("neutronFilter");
    neutronFilter->add("neutron");
    neutronFilter->add("e-");
    neutronFilter->add("e+");
    neutronFilter->add("gamma");
    ppLXeSD->SetFilter(neutronFilter);


    // only for debugging
//    auto muFilter = new G4SDParticleFilter("muFilter");
//    muFilter->add("mu-");
//    ppLXeSD->SetFilter(muFilter);



    G4cout <<"==>> finishing constructing TPC "<<G4endl;
    return true;
}


G4bool
XenonDetector::ConstructPMTArrays()
{
//box
//	G4double pHalfX;
//	G4double pHalfY;
//	G4double pHalfZ;

	G4double pOffsetX;
	G4double pOffsetY;
	G4double pOffsetZ;

//tubs
    G4double pRMin;
    G4double pRMax;
    G4double pDz;
    //G4double pSPhi;
//    G4double pDPhi;
//polycone
    //G4double   phiStart;
    //G4double   phiTotal;
//    G4int      numZPlane;
//    G4double   zPlane[4];
//    G4double   rInner[4];
//    G4double   rOuter[4];

	G4Material *Quartz = G4Material::GetMaterial("Quartz");
//	G4Material *Vacuum = G4Material::GetMaterial("Vacuum");
	G4Material *StainlessSteel = G4Material::GetMaterial("SS304LSteel");
	G4Material *Aluminium = G4Material::GetMaterial("PhotoCathodeAluminium");
//	G4Material *Cirlex = G4Material::GetMaterial("Cirlex");


	//---------------------------------- attributes ---------------------------------

	G4Colour hQUPIDWindowColor(1., 0.757, 0.024);
	G4VisAttributes *pQUPIDWindowVisAtt = new G4VisAttributes(hQUPIDWindowColor);
	pQUPIDWindowVisAtt->SetVisibility(true);


	G4Colour hQUPIDPhotocathodeColor(1., 0.082, 0.011);
	G4VisAttributes *pQUPIDPhotocathodeVisAtt = new G4VisAttributes(hQUPIDPhotocathodeColor);
	pQUPIDPhotocathodeVisAtt->SetVisibility(true);


	G4Colour hQUPIDAluminiumCoatingColor(1., 0.486, 0.027);
	G4VisAttributes *pQUPIDAluminiumCoatingVisAtt = new G4VisAttributes(hQUPIDAluminiumCoatingColor);
	pQUPIDAluminiumCoatingVisAtt->SetVisibility(true);


	G4Colour hQUPIDAPDColor(0.788, 0.188, 0.780);
	G4VisAttributes *pQUPIDAPDVisAtt = new G4VisAttributes(hQUPIDAPDColor);
	pQUPIDAPDVisAtt->SetVisibility(true);

	// SS Color
	G4Color hSSColor(1, 1.0, 1.0, 1.);
	G4VisAttributes *pSSVisAtt = new G4VisAttributes(hSSColor);
	pSSVisAtt -> SetVisibility(true);



	// ============================== Light sensor arrangement =================================
    pRMin                       = 0.0*mm;
	pRMax                       = GetGeometryParameter("PMTWidth");
	pDz                         = GetGeometryParameter("PMTThickness")/2.;
//	pOffsetZ                    = GetGeometryParameter("LXeHeight")/2.+GetGeometryParameter("PMTThickness")/2.;
	
	G4Tubs *pTopPMT             = new G4Tubs("pTopPMT", pRMin, pRMax, pDz, 0.0*deg, 360.0*deg);
    m_pTopPMTLogicalVolume      = new G4LogicalVolume(pTopPMT, StainlessSteel, "TopPMTVolume", 0, 0, 0);
    m_pTopPMTLogicalVolume->SetVisAttributes(pSSVisAtt);
    m_pTopPMTPhysicalVolume     = new G4PVPlacement(0, G4ThreeVector(), m_pTopPMTLogicalVolume, "TopPMT", m_pAirLayerLogicalVolume, false, 0);
    
//    G4Tubs *pBottomPMT             = new G4Tubs("pBottomPMT", pRMin, pRMax, pDz, 0.0*deg, 360.0*deg);
//    m_pBottomPMTLogicalVolume      = new G4LogicalVolume(pBottomPMT, StainlessSteel, "BottomPMTVolume", 0, 0, 0);
//    m_pBottomPMTLogicalVolume->SetVisAttributes(pSSVisAtt);
//    m_pBottomPMTPhysicalVolume     = new G4PVPlacement(0, G4ThreeVector(0, 0, -pOffsetZ), m_pBottomPMTLogicalVolume, "BottomPMT", m_pAirLayerLogicalVolume, false, 0);
    
  


	//------------------------------- PMT sensitivity -------------------------------
	G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
    PandaXPMTSD *pPmtSD     = new PandaXPMTSD("VolPmtSD");
    pSDManager->AddNewDetector(pPmtSD);
//    m_pLightSensorPhotoCathodeLogicalVolume->SetSensitiveDetector(pPmtSD);
    m_pTopPMTLogicalVolume->SetSensitiveDetector(pPmtSD);





	G4cout << "==>> finishing PMT array construction. "<<G4endl;
    return true;

}


G4bool
XenonDetector::DefineOpticalSurface()
{

//materials
	G4Material *Teflon = G4Material::GetMaterial("Teflon");
    G4Material *StainlessSteel = G4Material::GetMaterial("SS304LSteel");
    G4Material *Quartz = G4Material::GetMaterial("Quartz");//
    G4Material *Bialkali    = G4Material::GetMaterial("Bialkali");



	//================================== optical surfaces =================================
//	G4double dSigmaAlpha = 0.1;
	G4OpticalSurface *pTeflonOpticalSurface = new G4OpticalSurface("TeflonOpticalSurface",
		unified, polished, dielectric_metal);
	pTeflonOpticalSurface->SetMaterialPropertiesTable(Teflon->GetMaterialPropertiesTable());

	G4OpticalSurface *pSSOpticalSurface = new G4OpticalSurface("SSOpticalSurface",
		unified, polished, dielectric_metal);
	pSSOpticalSurface->SetMaterialPropertiesTable(StainlessSteel->GetMaterialPropertiesTable());

    G4OpticalSurface *pQuartzOpticalSurface = new G4OpticalSurface("QuartzOpticalSurface",
		glisur, polished, dielectric_metal);
//	pQuartzOpticalSurface->SetMaterialPropertiesTable(Quartz->GetMaterialPropertiesTable()); // somehow Quartz does not work
	pQuartzOpticalSurface->SetMaterialPropertiesTable(Bialkali->GetMaterialPropertiesTable());

	//================================== Define boundaries ==================================
//	stringstream hName;

//	// ------- LXe - Teflon -------
//	new G4LogicalSkinSurface("TeflonPanelSkinSurface", m_pTeflonPanelLogicalVolume, pTeflonOpticalSurface);
//	new G4LogicalBorderSurface("TopCapLXeBorderSurface", m_pLXeSDPhysicalVolume, m_pTopCapPhysicalVolume, pTeflonOpticalSurface);
//	new G4LogicalBorderSurface("BottomCapLXeBorderSurface", m_pLXeSDPhysicalVolume, m_pBottomCapPhysicalVolume, pTeflonOpticalSurface);
//
//	// ------ LXe - Wire ---------
//	new G4LogicalSkinSurface("WireSkinSurface", m_pWireLogicalVolume, pSSOpticalSurface);
//
//	// ------- LXe - light sensor components (excluding photocathode) ------
//	new G4LogicalSkinSurface("LightSensorWindowSkinSurface", m_pLightSensorWindowLogicalVolume, pQuartzOpticalSurface);
//	new G4LogicalSkinSurface("LightSensorCasingSkinSurface", m_pLightSensorCasingLogicalVolume, pSSOpticalSurface);


//---------------- finish defining optical surface--------------
	G4cout<<"==>> finishing defining optical surface =========="<<G4endl;
	return true;
}



void
XenonDetector::GetSidePMTOffsetXY(G4int Index, G4double &pOffsetX, G4double &pOffsetY)
{
    ///////////////////////////////////////////////////
    // function for extracting the offset X-Y of a given side PMT index
    // It is a matrix of sensor
    ///////////////////////////////////////////////////
    // some input parameters
	G4double LightSensorWidth       = GetGeometryParameter("LightSensorWidth");
	G4int NumberOfSidePMTs          = GetGeometryParameter("NumberOfSidePMTs");
	G4double SidePMTDistance        = GetGeometryParameter("SidePMTDistance");

	G4int NumberOfPMTsEachSide      = sqrt(NumberOfSidePMTs);
	G4double pMin                   = 0;
	if(NumberOfPMTsEachSide%2==0)
	{
	    pMin                          = -(((double)NumberOfPMTsEachSide/2) + 0.5)*SidePMTDistance;
	}
	else
	{
	    pMin                          = -NumberOfPMTsEachSide/2*SidePMTDistance;
	}

	int ii      = Index/NumberOfPMTsEachSide;
	int jj      = Index%NumberOfPMTsEachSide;
	pOffsetX    = ((double)ii)*SidePMTDistance + pMin;
	pOffsetY    = ((double)jj)*SidePMTDistance + pMin;
	return;

}
