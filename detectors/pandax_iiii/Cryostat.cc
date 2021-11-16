#include "Cryostat.hh"
#include "detector/BambooDetectorFactory.hh"
#include "BambooGlobalVariables.hh"
#include "analysis/PandaXSensitiveDetector.hh"
#include <TString.h>
#include <TObjArray.h>
#include <TObjString.h>

#include <G4Tubs.hh>
#include <G4Ellipsoid.hh>
#include <G4UnionSolid.hh>

#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>
#include <G4Torus.hh>

DetectorRegister<Cryostat> Cryostat::reg("Cryostat");
/*
namespace {

  BambooDetectorPart * createCryostat ()
  {
    return new Cryostat("Cryostat");
  }

  const std::string CryostatName("Cryostat");

  const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(CryostatName, createCryostat);
}
*/

Cryostat::Cryostat (const G4String & name): BambooDetectorPart(name)
{
  BambooGlobalVariables *bgv = BambooGlobalVariables::Instance();
  G4cout << "Cryostat found..." << G4endl;
}



G4bool Cryostat::construct()
{


    DefineGeometryParameters("PandaX-V");

    ConstructOuterVessel();
    ConstructOuterVesselFlange();
    ConstructCryoVacuum();
    ConstructCalibration();
//    ConstructMiddleVessel();


}




G4bool Cryostat::ConstructOuterVessel()
{
   

  G4double pRMin;
  G4double pRMax;
  G4double pDz;


  G4double  pxSemiAxis;
  G4double  pySemiAxis;
  G4double  pzSemiAxis;
  G4double  pzBottomCut;
  G4double  pzTopCut;

  G4Material *StainlessSteel = G4Material::GetMaterial("SS304LSteel");
  

  pRMax = GetGeometryParameter("OuterVesselOuterRadius");
  pRMin = 0;
  pDz   = GetGeometryParameter("OuterVesselHeight")/2;

  G4Tubs *pOuterVesselTub = new G4Tubs("OuterVesselTub", pRMin, pRMax, pDz, 0.0*deg, 360.*deg);


  pxSemiAxis = GetGeometryParameter("OuterVesselOuterDomeRadius");
  pySemiAxis = pxSemiAxis;
  pzSemiAxis = pxSemiAxis;
  pzTopCut      = 0.0-(pxSemiAxis-GetGeometryParameter("OuterVesselOuterDomeHeight"));
  pzBottomCut   = 0.0-pxSemiAxis;
  G4Ellipsoid *pOuterVesselDome = new G4Ellipsoid("OuterVesselDome",pxSemiAxis,pySemiAxis,pzSemiAxis,pzBottomCut,pzTopCut);


  G4RotationMatrix * rotateTopDome = new G4RotationMatrix();
  rotateTopDome->rotateX(180*deg);

  G4double outerzshift =  GetGeometryParameter("OuterVesselOuterDomeRadius")-GetGeometryParameter("OuterVesselHeight")/2.0 -GetGeometryParameter("OuterVesselOuterDomeHeight");


  G4UnionSolid* pOuterVesselTop = new G4UnionSolid("OuterVesselTop", pOuterVesselTub, pOuterVesselDome, rotateTopDome, G4ThreeVector(0,0, -outerzshift));

  G4UnionSolid* pOuterVesselVolume = new G4UnionSolid("OuterVesselVolume", pOuterVesselTop, pOuterVesselDome, 0, G4ThreeVector(0,0, outerzshift));


  m_pOuterVesselLogicalVolume = new G4LogicalVolume(pOuterVesselVolume, StainlessSteel, "OuterVessel", 0, 0, 0);

//  m_pOuterVesselLogicalVolume = new G4LogicalVolume(pOuterVesselTub, StainlessSteel, "OuterVessel", 0, 0, 0);
//  m_pOuterVesselPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0,0, GetGeometryParameter("DetectorZShift") + GetGeometryParameter("OuterVesselzshift") ), m_pOuterVesselLogicalVolume, "OuterVessel", _parentPart->getContainerLogicalVolume(), false, 0);

  m_pOuterVesselPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0,0, GetGeometryParameter("DetectorZShift")), m_pOuterVesselLogicalVolume, "OuterVessel", parentPart_->getContainerLogicalVolume(), false, 0);


  G4Colour hOuterVesselColor(1, 0.3, 0.2, 1);
  G4VisAttributes *pOuterVesselVisAtt = new G4VisAttributes(hOuterVesselColor);
  pOuterVesselVisAtt->SetVisibility(false);
  m_pOuterVesselLogicalVolume->SetVisAttributes(pOuterVesselVisAtt);

}




G4bool Cryostat::ConstructOuterVesselFlange()
{
   

  G4double pRMin;
  G4double pRMax;
  G4double pDz;

  G4Material *StainlessSteel = G4Material::GetMaterial("SS304LSteel");

 
  pRMin = GetGeometryParameter("OuterVesselFlangeInnerRadius");
  pRMax = GetGeometryParameter("OuterVesselFlangeOuterRadius");
  pDz   = GetGeometryParameter("OuterVesselFlangeHeight")/2.0;

  G4Tubs *pOuterVesselFlangeTubs =  new G4Tubs("OuterVesselFlangeTubs", pRMin, pRMax, pDz, 0*deg, 360*deg);

 
  m_pOuterVesselFlangeLogicalVolume = new G4LogicalVolume(pOuterVesselFlangeTubs, StainlessSteel, "OuterVesselFlangeVolume",0,0,0);
  m_pOuterVesselFlangePhysicalVolume = new G4PVPlacement(0,G4ThreeVector(0,0, GetGeometryParameter("OuterVesselFlangeZShift")),m_pOuterVesselFlangeLogicalVolume, "OuterVesselFlange", parentPart_->getContainerLogicalVolume(), false ,0);


  G4Colour hOuterVesselFlangeColor(0, 0, 1, 1);
  G4VisAttributes *pOuterVesselFlangeVisAtt = new G4VisAttributes(hOuterVesselFlangeColor);
  pOuterVesselFlangeVisAtt->SetVisibility(false);
  m_pOuterVesselFlangeLogicalVolume->SetVisAttributes(pOuterVesselFlangeVisAtt);


return true;

}




G4bool Cryostat::ConstructCryoVacuum()
{

  G4double pRMin;
  G4double pRMax;
  G4double pDz;

  G4double  pxSemiAxis;
  G4double  pySemiAxis;
  G4double  pzSemiAxis;
  G4double  pzBottomCut;
  G4double  pzTopCut;
  

  G4Material *Copper = G4Material::GetMaterial("Copper");
  G4Material *Vacuum = G4Material::GetMaterial("Vacuum");

  pRMax = GetGeometryParameter("CryoVacuumRadius");
  pRMin = 0;
  pDz   = GetGeometryParameter("CryoVacuumHeight")/2 ;
  G4Tubs *pCryoVacuumTub = new G4Tubs("CryoVacuumTub", pRMin, pRMax, pDz, 0.0*deg, 360.*deg);



  pxSemiAxis = GetGeometryParameter("CryoVacuumDomeRadius");
  pySemiAxis = pxSemiAxis;
  pzSemiAxis = pxSemiAxis;
  pzTopCut      = 0.0-(pxSemiAxis-GetGeometryParameter("CryoVacuumDomeHeight"));
  pzBottomCut   = 0.0-pxSemiAxis;
  G4Ellipsoid *pCryoVacuumDome = new G4Ellipsoid("CryoVacuumDome",pxSemiAxis,pySemiAxis,pzSemiAxis,pzBottomCut,pzTopCut);


  G4RotationMatrix * rotateTopDome = new G4RotationMatrix();
  rotateTopDome->rotateX(180*deg);

  G4double outerzshift =  GetGeometryParameter("CryoVacuumDomeRadius")-GetGeometryParameter("CryoVacuumHeight")/2.0
  -GetGeometryParameter("CryoVacuumDomeHeight");



  G4UnionSolid* pCryoVacuumTop = new G4UnionSolid("CryoVacuumTop", pCryoVacuumTub, pCryoVacuumDome, rotateTopDome, G4ThreeVector(0,0, -outerzshift));

  G4UnionSolid* pCryoVacuumVolume = new G4UnionSolid("CryoVacuumVolume", pCryoVacuumTop, pCryoVacuumDome, 0, G4ThreeVector(0,0, outerzshift));


  
  m_pCryoVacuumLogicalVolume = new G4LogicalVolume(pCryoVacuumVolume, Vacuum, "CryoVacuum", 0, 0, 0);

  m_pCryoVacuumPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0,0, 0), m_pCryoVacuumLogicalVolume, "CryoVacuum", m_pOuterVesselLogicalVolume, false, 0);


  G4Colour hCryoVacuumColor(0, 1, 0, 1);
  G4VisAttributes *pCryoVacuumVisAtt = new G4VisAttributes(hCryoVacuumColor);
  pCryoVacuumVisAtt->SetVisibility(false);
  m_pCryoVacuumLogicalVolume->SetVisAttributes(pCryoVacuumVisAtt);

 partContainerLogicalVolume_ =  m_pCryoVacuumLogicalVolume;



  return true;
 
      

}







G4bool Cryostat::ConstructCalibration()
{



  G4double pRMin;
  G4double pRMax;
  G4double pDz;

  G4double pRtor;

  G4double pSPhi;
  G4double pDPhi;



  

  G4Material *Copper = G4Material::GetMaterial("Copper");
  G4Material *StainlessSteel = G4Material::GetMaterial("SS304LSteel");





 //=================================== calibration source tube ==============================================//
  
  
  pRMin = GetGeometryParameter("CalibrationSourceTubeInnerRadius");
  pRMax = GetGeometryParameter("CalibrationSourceTubeOuterRadius");
  pRtor = GetGeometryParameter("CalibrationSourceTubeTorusRadius");
  G4Torus *pCalibrationSourceTubeTorus = new G4Torus("CalibrationSourceTubeTorus", pRMin, pRMax, pRtor, 0.0*deg, 360.0*deg);
  
  m_pCalibrationSourceTubeLogicalVolume = new G4LogicalVolume(pCalibrationSourceTubeTorus, Copper, "CalibrationSourceTube", 0, 0, 0);

  m_pCalibrationSourceTubePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0,0,0), m_pCalibrationSourceTubeLogicalVolume, "CalibrationSourceTube", m_pCryoVacuumLogicalVolume, false, 0);
	

  
  G4Colour hCalibrationSourceTubeColor(1, 0, 0, 1);
  G4VisAttributes *pCalibrationSourceTubeVisAtt = new G4VisAttributes(hCalibrationSourceTubeColor);
  pCalibrationSourceTubeVisAtt->SetVisibility(false);
  m_pCalibrationSourceTubeLogicalVolume->SetVisAttributes(pCalibrationSourceTubeVisAtt);
    
  

//========================================= Calibration Source SS ===========================//


  pRMax = GetGeometryParameter("CalibrationSourceSSRadius");
  pRMin = 0.0;
  pDz   = GetGeometryParameter("CalibrationSourceSSHeight")/2;

  G4Tubs *pCalibrationSourceSSTubs = new G4Tubs("CalibrationSourceSSTubs", pRMin, pRMax, pDz, 0.0*deg, 360.0*deg);
  m_pCalibrationSourceSSLogicalVolume = new G4LogicalVolume(pCalibrationSourceSSTubs, StainlessSteel, "CalibrationSourceSSVolume", 0, 0, 0);
 
  G4double xpos = GetGeometryParameter("CalibrationSourceSSXpos");
  G4double ypos = GetGeometryParameter("CalibrationSourceSSYpos");
  G4double zpos = GetGeometryParameter("CalibrationSourceSSZshift");
  G4RotationMatrix * ssRotation = new G4RotationMatrix();
  ssRotation->rotateY(90.0*deg);
  ssRotation->rotateX(45.0*deg);
  m_pCalibrationSourceSSPhysicalVolume = new G4PVPlacement(ssRotation, G4ThreeVector(xpos,ypos,zpos), m_pCalibrationSourceSSLogicalVolume, "CalibrationSourceSS", m_pCryoVacuumLogicalVolume, false, 0);

  G4Colour hCalibrationSourceSSColor(1, 0, 0, 1);
  G4VisAttributes *pCalibrationSourceSSVisAtt = new G4VisAttributes(hCalibrationSourceSSColor);
  pCalibrationSourceSSVisAtt->SetVisibility(false);
  m_pCalibrationSourceSSLogicalVolume->SetVisAttributes(pCalibrationSourceSSVisAtt);


//========================================= Calibration Source ===========================//

  pRMax = GetGeometryParameter("CalibrationSourceRadius");
  pRMin = 0.0;
  pDz   = GetGeometryParameter("CalibrationSourceHeight")/2;

  G4Tubs *pCalibrationSourceTubs = new G4Tubs("CalibrationSourceTubs", pRMin, pRMax, pDz, 0.0*deg, 360.0*deg);
  m_pCalibrationSourceLogicalVolume = new G4LogicalVolume(pCalibrationSourceTubs, StainlessSteel, "CalibrationSourceVolume", 0, 0, 0);
  xpos = 0.0;
  ypos = 0.0;
  zpos = GetGeometryParameter("CalibrationSourceToSSZshift");
  m_pCalibrationSourcePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(xpos,ypos,zpos), m_pCalibrationSourceLogicalVolume, "CalibrationSource", m_pCalibrationSourceSSLogicalVolume, false, 0);


  G4Colour hCalibrationSourceColor(0, 1, 0, 1);
  G4VisAttributes *pCalibrationSourceVisAtt = new G4VisAttributes(hCalibrationSourceColor);
  pCalibrationSourceVisAtt->SetVisibility(false);
  m_pCalibrationSourceLogicalVolume->SetVisAttributes(pCalibrationSourceVisAtt);

  return true;

}



G4bool Cryostat::ConstructMiddleVessel()
{
   

  G4double pRMin;
  G4double pRMax;
  G4double pDz;



  G4Material *Copper = G4Material::GetMaterial("Copper");


  pRMin = GetGeometryParameter("MiddleVesselInnerRadius");
  pRMax = GetGeometryParameter("MiddleVesselOuterRadius");
  pDz   = GetGeometryParameter("MiddleVesselHeight")/2;

  G4Tubs *pMiddleVesselTub = new G4Tubs("MiddleVesselTub", pRMin, pRMax, pDz, 0.0*deg, 360.*deg);


  m_pMiddleVesselLogicalVolume = new G4LogicalVolume(pMiddleVesselTub, Copper, "MiddleVessel", 0, 0, 0);
 m_pMiddleVesselPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0,0, GetGeometryParameter("MiddleVesselZShift")), m_pMiddleVesselLogicalVolume, "MiddleVessel", m_pCryoVacuumLogicalVolume, false, 0);



  G4Colour hMiddleVesselColor(0, 0, 1, 1);
  G4VisAttributes *pMiddleVesselVisAtt = new G4VisAttributes(hMiddleVesselColor);
  pMiddleVesselVisAtt->SetVisibility(false);
  m_pMiddleVesselLogicalVolume->SetVisAttributes(pMiddleVesselVisAtt);

}







