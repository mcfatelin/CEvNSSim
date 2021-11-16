#include "PandaXLab.hh"
#include "detector/BambooDetectorFactory.hh"
#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"
#include "analysis/PandaXSensitiveDetector.hh"

#include <G4Material.hh>
#include <G4ThreeVector.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4SDManager.hh>
#include <G4VSDFilter.hh>
#include <G4SDParticleFilter.hh>
#include <G4VisAttributes.hh>
#include <G4Tubs.hh>
#include <G4UnionSolid.hh>

DetectorRegister<PandaXLab> PandaXLab::reg("PandaXLab");

#define DEBUG_GEOMETRY

/*
namespace 
{

  BambooDetectorPart * createPandaXLab ()
  {
    return new PandaXLab("PandaXLab");
  }

  const std::string PandaXLabName("PandaXLab");

  const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(PandaXLabName, createPandaXLab);
}
*/




PandaXLab::PandaXLab (const G4String & name): BambooDetectorPart(name)
{

  //BambooGlobalVariables *bgv = BambooGlobalVariables::Instance();
  G4cout << "Lab found..." << G4endl;

}





G4bool PandaXLab::construct ()
{
#ifdef DEBUG_GEOMETRY
  G4cout << "***DEBUG***: loaded - PandaXLab::Construct()" << G4endl;
#endif

    DefineGeometryParameters("PandaX-V"); //!!! this function had been available on the base class #Pick

    ConstructAir();
    //ConstructMarbleWall();
    //ConstructInAir();
    //ConstructConcreteWall();

    //ConstructSteelWall();
    //ConstructWaterSpace();

    //ConstructTestConcreteWall();
    //ConstructTestSteelWall();

    //ConstructTestSideConcreteWall();
    //ConstructTestSideSteelWall();

	return true; // + #Pick
}

G4bool PandaXLab::ConstructAir()
{
 
#ifdef DEBUG_GEOMETRY
  G4cout << "***DEBUG***: loaded - PandaXLab::ConstructAir()" << G4endl;
#endif
 
  auto air = G4Material::GetMaterial("G4_AIR"); 

  //G4SDManager *pSDManager = G4SDManager::GetSDMpointer();

  
 
  //G4double pRMin;
  //G4double pRMax;
  //G4double pDz;

 

  G4Box * AirBox = new G4Box("AirBox", GetGeometryParameter("AirLength")/2., GetGeometryParameter("AirWidth")/2., GetGeometryParameter("AirHeight")/2.);
  //auto AirBox = new G4Box("AirBox", 30.*m/2., 30.*m/2., 20.*m/2.);
  
  AirLogicalVolume = new G4LogicalVolume(AirBox, air, "AirBoxLog", 0, 0, 0);
  partLogicalVolume_ = AirLogicalVolume;
  AirPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(), partLogicalVolume_, "RockWall", 0, false, 0);
  partPhysicalVolume_ = AirPhysicalVolume;
  
  G4VisAttributes * AirVis = new G4VisAttributes();
  AirVis->SetColour(0, 0, 1, 0.3);
  AirVis->SetVisibility(true);
  AirLogicalVolume->SetVisAttributes(AirVis);

  partContainerLogicalVolume_ = AirLogicalVolume;
  
  return true;
}


G4bool PandaXLab::ConstructMarbleWall()
{
    
  G4Material * marble = G4Material::GetMaterial("Marble");

  G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
   
  //G4double pRMin;
  //G4double pRMax;
  //G4double pDz;
  
  
  G4Box * MarbleBox = new G4Box("MarbleBox", GetGeometryParameter("MarbleLength")/2., GetGeometryParameter("MarbleWidth")/2., GetGeometryParameter("MarbleHeight")/2.);
  MarbleWallLogicalVolume = new G4LogicalVolume(MarbleBox, marble, "MarbleBoxLog", 0, 0, 0);
  
  
  MarbleWallPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0,   - GetGeometryParameter("MarbleHeight")/2), MarbleWallLogicalVolume, "MarbleWall", AirLogicalVolume, false, 0);


  PandaXSensitiveDetector * pMarbleWallSD = new PandaXSensitiveDetector("MarbleWallSD");
  pSDManager->AddNewDetector(pMarbleWallSD);
  MarbleWallLogicalVolume->SetSensitiveDetector(pMarbleWallSD);



  G4VisAttributes * MarbleVis = new G4VisAttributes();
  MarbleVis->SetColour(1, 1, 0 , 2);
  MarbleVis->SetVisibility(false);
  MarbleWallLogicalVolume->SetVisAttributes(MarbleVis);
  
  return true;
}


G4bool PandaXLab::ConstructInAir()
{

  G4Material * air = G4Material::GetMaterial("G4_AIR"); 

  //G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
  
 
  G4double pRMin;
  G4double pRMax;
  G4double pDz;
    
  G4Box * pInAirBox = new G4Box("InAirBox", GetGeometryParameter("InAirLength")/2., GetGeometryParameter("InAirWidth")/2., GetGeometryParameter("InAirHeight")/2.);

  pRMin = 0;
  pRMax = GetGeometryParameter("InAirWidth")/2.;
  pDz   = GetGeometryParameter("InAirHeight")/2;
  
  G4Tubs *pInAirWallTubLeft = new G4Tubs("InAirWallTubLeft", pRMin, pRMax, pDz, 0.*deg, 180.*deg);
  G4RotationMatrix * rotateInAirWallTubLeft = new G4RotationMatrix();
  rotateInAirWallTubLeft->rotateZ(90.0*deg);
  
  
  G4Tubs *pInAirWallTubRight = new G4Tubs("InAirWallTubRight", pRMin, pRMax, pDz, 0.*deg, 180.*deg);
  G4RotationMatrix * rotateInAirWallTubRight = new G4RotationMatrix();
  rotateInAirWallTubRight->rotateZ(-90.0*deg);
  
  
  G4UnionSolid* pInAirWallLeft = new G4UnionSolid("InAirWallLeft", pInAirBox, pInAirWallTubLeft, rotateInAirWallTubLeft, G4ThreeVector( GetGeometryParameter("InAirLength")/2,0,0));
  G4UnionSolid* pInAirWall = new G4UnionSolid("InAirWall", pInAirWallLeft, pInAirWallTubRight, rotateInAirWallTubRight, G4ThreeVector(- GetGeometryParameter("InAirLength")/2,0,0));



  InAirWallLogicalVolume = new G4LogicalVolume(pInAirWall, air, "InAirBoxLog", 0, 0, 0);
  
  
  InAirWallPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, GetGeometryParameter("MarbleHeight")/2 -GetGeometryParameter("InAirHeight")/2 ), InAirWallLogicalVolume, "InAirWall", MarbleWallLogicalVolume, false, 0);

  G4VisAttributes * InAirVis = new G4VisAttributes();
  InAirVis->SetColour(0.5, 0.5, 0 , 1);
  InAirVis->SetVisibility(false);
  InAirWallLogicalVolume->SetVisAttributes(InAirVis);

  return true;
}




G4bool PandaXLab::ConstructConcreteWall()
{
    
  G4Material * concrete = G4Material::GetMaterial("Concrete");

  G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
  
 
  G4double pRMin;
  G4double pRMax;
  G4double pDz;
 
 
  pRMin = 0;
  pRMax = GetGeometryParameter("ConcreteWidth")/2.;
  pDz   = GetGeometryParameter("ConcreteHeight")/2;

  G4Box * pConcreteBox = new G4Box("ConcreteBox", GetGeometryParameter("ConcreteLength")/2., GetGeometryParameter("ConcreteWidth")/2., GetGeometryParameter("ConcreteHeight")/2.);
  
  G4Tubs *pConcreteWallTubLeft = new G4Tubs("ConcreteWallTubLeft", pRMin, pRMax, pDz, 0.*deg, 180.*deg);
  G4RotationMatrix * rotateConcreteWallTubLeft = new G4RotationMatrix();
  rotateConcreteWallTubLeft->rotateZ(90.0*deg);
  
  
  G4Tubs *pConcreteWallTubRight = new G4Tubs("ConcreteWallTubRight", pRMin, pRMax, pDz, 0.*deg, 180.*deg);
  G4RotationMatrix * rotateConcreteWallTubRight = new G4RotationMatrix();
  rotateConcreteWallTubRight->rotateZ(-90.0*deg);
  
  
  G4UnionSolid* pConcreteWallLeft = new G4UnionSolid("ConcreteWallLeft", pConcreteBox, pConcreteWallTubLeft, rotateConcreteWallTubLeft, 
G4ThreeVector( GetGeometryParameter("ConcreteLength")/2,0,0));
  G4UnionSolid* pConcreteWall = new G4UnionSolid("ConcreteWall", pConcreteWallLeft, pConcreteWallTubRight, rotateConcreteWallTubRight, G4ThreeVector(- GetGeometryParameter("ConcreteLength")/2,0,0));



  ConcreteWallLogicalVolume = new G4LogicalVolume(pConcreteWall, concrete, "ConcreteBoxLog", 0, 0, 0);
  
  
  ConcreteWallPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, GetGeometryParameter("InAirHeight")/2 - GetGeometryParameter("ConcreteHeight")/2 ), ConcreteWallLogicalVolume, "ConcreteWall", InAirWallLogicalVolume, false, 0);


  PandaXSensitiveDetector * pConcreteWallSD = new PandaXSensitiveDetector("ConcreteWallSD");
  pSDManager->AddNewDetector(pConcreteWallSD);
  ConcreteWallLogicalVolume->SetSensitiveDetector(pConcreteWallSD);


  G4VisAttributes * concreteVis = new G4VisAttributes();
  concreteVis->SetColour(1, 0, 0 , 2);
  concreteVis->SetVisibility(false);
  ConcreteWallLogicalVolume->SetVisAttributes(concreteVis);


  return true;
  
 }



G4bool PandaXLab::ConstructSteelWall()
{
   

  G4Material * steel = G4Material::GetMaterial("SS304LSteel"); 

  G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
  
 
 
  G4double pRMin;
  G4double pRMax;
  G4double pDz;

  
  G4Box * pSteelBox = new G4Box("SteelBox", GetGeometryParameter("SteelLength")/2., GetGeometryParameter("SteelWidth")/2., GetGeometryParameter("SteelHeight")/2.);

  pRMin = 0;
  pRMax = GetGeometryParameter("SteelWidth")/2.;
  pDz   = GetGeometryParameter("SteelHeight")/2;
  
  G4Tubs *pSteelWallTubLeft = new G4Tubs("SteelWallTubLeft", pRMin, pRMax, pDz, 0.*deg, 180.*deg);

  G4RotationMatrix * rotateSteelWallTubLeft = new G4RotationMatrix();
  rotateSteelWallTubLeft->rotateZ(90.0*deg);
  
  
  G4Tubs *pSteelWallTubRight = new G4Tubs("SteelWallTubRight", pRMin, pRMax, pDz, 0.*deg, 180.*deg);

  G4RotationMatrix * rotateSteelWallTubRight = new G4RotationMatrix();
  rotateSteelWallTubRight->rotateZ(-90.0*deg);


  G4UnionSolid* pSteelWallLeft = new G4UnionSolid("SteelWallLeft", pSteelBox, pSteelWallTubLeft, rotateSteelWallTubLeft, G4ThreeVector(GetGeometryParameter("SteelLength")/2,0,0));

  G4UnionSolid* pSteelWall = new G4UnionSolid("SteelWall", pSteelWallLeft, pSteelWallTubRight, rotateSteelWallTubRight, G4ThreeVector(-GetGeometryParameter("SteelLength")/2,0,0));



  SteelWallLogicalVolume = new G4LogicalVolume(pSteelWall, steel, "SteelBoxLog", 0, 0, 0);

  SteelWallPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, GetGeometryParameter("InAirHeight")/2 - GetGeometryParameter("SteelHeight")/2  ), SteelWallLogicalVolume, "SteelWall", ConcreteWallLogicalVolume, false, 0);


  PandaXSensitiveDetector * pSteelWallSD = new PandaXSensitiveDetector("SteelWallSD");
  pSDManager->AddNewDetector(pSteelWallSD);
  SteelWallLogicalVolume->SetSensitiveDetector(pSteelWallSD);


  G4VisAttributes * SteelVis = new G4VisAttributes();
  SteelVis->SetColour(0, 1, 0 , 2);
  SteelVis->SetVisibility(false);
  SteelWallLogicalVolume->SetVisAttributes(SteelVis);
  
  return true;
}
  

G4bool PandaXLab::ConstructWaterSpace()
{
   

  G4Material * water = G4Material::GetMaterial("Water");  

  G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
 
 
  G4double pRMin;
  G4double pRMax;
  G4double pDz;

  
  G4Box * pWaterBox = new G4Box("WaterBox", GetGeometryParameter("WaterLength")/2., GetGeometryParameter("WaterWidth")/2., GetGeometryParameter("WaterHeight")/2.);

  pRMin = 0;
  pRMax = GetGeometryParameter("WaterWidth")/2.;
  pDz   = GetGeometryParameter("WaterHeight")/2;
  
  G4Tubs *pWaterSpaceTubLeft = new G4Tubs("WaterSpaceTubLeft", pRMin, pRMax, pDz, 0.*deg, 180.*deg);

  G4RotationMatrix * rotateWaterSpaceTubLeft = new G4RotationMatrix();
  rotateWaterSpaceTubLeft->rotateZ(90.0*deg);
  
  
  G4Tubs *pWaterSpaceTubRight = new G4Tubs("WaterSpaceTubRight", pRMin, pRMax, pDz, 0.*deg, 180.*deg);

  G4RotationMatrix * rotateWaterSpaceTubRight = new G4RotationMatrix();
  rotateWaterSpaceTubRight->rotateZ(-90.0*deg);


  G4UnionSolid* pWaterSpaceLeft = new G4UnionSolid("WaterSpaceLeft", pWaterBox, pWaterSpaceTubLeft, rotateWaterSpaceTubLeft, G4ThreeVector(GetGeometryParameter("WaterLength")/2,0,0));

  G4UnionSolid* pWaterSpace = new G4UnionSolid("WaterSpace", pWaterSpaceLeft, pWaterSpaceTubRight, rotateWaterSpaceTubRight, G4ThreeVector(-GetGeometryParameter("WaterLength")/2,0,0));



  WaterSpaceLogicalVolume = new G4LogicalVolume(pWaterSpace, water, "WaterBoxLog", 0, 0, 0);
  WaterSpacePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, GetGeometryParameter("SteelHeight")/2 - GetGeometryParameter("WaterHeight")/2  ), WaterSpaceLogicalVolume, "WaterSpace", SteelWallLogicalVolume, false, 0);


  PandaXSensitiveDetector * pWaterSpaceSD = new PandaXSensitiveDetector("WaterSpaceSD");
  pSDManager->AddNewDetector(pWaterSpaceSD);
  WaterSpaceLogicalVolume->SetSensitiveDetector(pWaterSpaceSD);


  G4VisAttributes * WaterSpaceVis = new G4VisAttributes();
  WaterSpaceVis->SetColour(0, 0, 1 , 2);
  WaterSpaceVis->SetVisibility(false);
  WaterSpaceLogicalVolume->SetVisAttributes(WaterSpaceVis);

  partContainerLogicalVolume_ = WaterSpaceLogicalVolume;
  
  return true;
}






G4bool  PandaXLab::ConstructTestConcreteWall()
{
    

  G4Material *Material = G4Material::GetMaterial("Concrete");

  G4double pRMin;
  G4double pRMax;
  G4double pDz;


  pRMin = 0;
  pRMax = GetGeometryParameter("TestModelRadius");
  pDz   = GetGeometryParameter("TestModelThickness")/2;



  G4Tubs *pTestConcreteWallTub = new G4Tubs("TestConcreteWallTub", pRMin, pRMax, pDz, 0.*deg,360.*deg);

  TestConcreteWallLogicalVolume = new G4LogicalVolume(pTestConcreteWallTub, Material, "TestConcreteWallTub", 0, 0, 0);
  TestConcreteWallPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, GetGeometryParameter("TestModelZShift")), TestConcreteWallLogicalVolume, "TestConcreteWall", WaterSpaceLogicalVolume, false, 0);


  G4VisAttributes * TestConcreteWallVis = new G4VisAttributes();
  TestConcreteWallVis->SetColour(1, 0, 0 , 1);
  TestConcreteWallVis->SetVisibility(true);
  TestConcreteWallLogicalVolume->SetVisAttributes(TestConcreteWallVis);
  
  return true;
}






G4bool  PandaXLab::ConstructTestSteelWall()
{
    

   G4Material *Material = G4Material::GetMaterial("SS304LSteel");


  G4double pRMin;
  G4double pRMax;
  G4double pDz;

  pRMin = 0;
  pRMax = GetGeometryParameter("TestModelRadius");
  pDz   = GetGeometryParameter("TestModelThickness")/2;


  G4Tubs *pTestSteelWallTub = new G4Tubs("TestSteelWallTub", pRMin, pRMax, pDz, 0.*deg,360.*deg);

  TestSteelWallLogicalVolume = new G4LogicalVolume(pTestSteelWallTub, Material, "TestSteelWallTub", 0, 0, 0);
  TestSteelWallPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0,GetGeometryParameter("TestModelZShift")), TestSteelWallLogicalVolume, "TestSteelWall", WaterSpaceLogicalVolume, false, 0);


  G4VisAttributes * TestSteelWallVis = new G4VisAttributes();
  TestSteelWallVis->SetColour(0, 1, 0 , 1);
  TestSteelWallVis->SetVisibility(true);
  TestSteelWallLogicalVolume->SetVisAttributes(TestSteelWallVis);
  
  return true;
}








G4bool  PandaXLab::ConstructTestSideConcreteWall()
{
    

   G4Material *Material = G4Material::GetMaterial("SS304LSteel");

  G4Box * pTestSideConcreteWallBox = new G4Box("TestSideConcreteWallBox", GetGeometryParameter("TestSideModelThickness")/2., GetGeometryParameter("TestSideModelWidth")/2., GetGeometryParameter("TestSideModelHeight")/2.);

  TestSideConcreteWallLogicalVolume = new G4LogicalVolume(pTestSideConcreteWallBox, Material, "pTestSideConcreteWallBox", 0, 0, 0);
  TestSideConcreteWallPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(GetGeometryParameter("TestSideModelXShift"), 0,0), TestSideConcreteWallLogicalVolume, "TestSideConcreteWall", WaterSpaceLogicalVolume, false, 0);


  G4VisAttributes * TestSideConcreteWallVis = new G4VisAttributes();
  TestSideConcreteWallVis->SetColour(1, 0, 0 , 1);
  TestSideConcreteWallVis->SetVisibility(true);
  TestSideConcreteWallLogicalVolume->SetVisAttributes(TestSideConcreteWallVis);
  
  return true;
}




G4bool  PandaXLab::ConstructTestSideSteelWall()
{
    

   G4Material *Material = G4Material::GetMaterial("SS304LSteel");



  G4Box * pTestSideSteelWallBox = new G4Box("TestSideSteelWallBox", GetGeometryParameter("TestSideModelThickness")/2., GetGeometryParameter("TestSideModelWidth")/2., GetGeometryParameter("TestSideModelHeight")/2.);

  TestSideSteelWallLogicalVolume = new G4LogicalVolume(pTestSideSteelWallBox, Material, "pTestSideSteelWallBox", 0, 0, 0);
  TestSideSteelWallPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(GetGeometryParameter("TestSideModelXShift"), 0,0), TestSideSteelWallLogicalVolume, "TestSideSteelWall", WaterSpaceLogicalVolume, false, 0);


  G4VisAttributes * TestSideSteelWallVis = new G4VisAttributes();
  TestSideSteelWallVis->SetColour(0, 1, 0 , 1);
  TestSideSteelWallVis->SetVisibility(true);
  TestSideSteelWallLogicalVolume->SetVisAttributes(TestSideSteelWallVis);
  
  return true;
}



