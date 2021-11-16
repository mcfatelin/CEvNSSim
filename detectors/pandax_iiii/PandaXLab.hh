#ifndef PANDAXLAB_H
#define PANDAXLAB_H

#include "detector/BambooDetectorPart.hh"
#include "detector/BambooDetectorFactory.hh"


//! The class to simulate the laboratory for PandaX
/*!
 * This class is used to simulate the laboratory for PandaX.
 * The inner length, width and height need to be provided by the user.
 * The thickness of concrete/rock walls will also be provided by the user.
 * The rock walls are outside of the concrete walls.
 * The default unit of length is mm.
 */
class PandaXLab : public BambooDetectorPart
{

public:

  PandaXLab(const G4String &name);

  virtual G4bool construct();

	static DetectorRegister<PandaXLab> reg;
    
	G4bool     ConstructAir();
    G4bool     ConstructMarbleWall();
    G4bool     ConstructConcreteWall();
    G4bool     ConstructInAir();
    G4bool     ConstructSteelWall();
    G4bool     ConstructWaterSpace();
    G4bool     ConstructTestConcreteWall();
    G4bool     ConstructTestSteelWall();

    G4bool     ConstructTestSideConcreteWall();
    G4bool     ConstructTestSideSteelWall();
  

private:
  
   double _radius;
   double _thickness;
   double _ZShift;
  
  G4LogicalVolume * MarbleWallLogicalVolume; 
  G4VPhysicalVolume * MarbleWallPhysicalVolume; 
  
  G4LogicalVolume * ConcreteWallLogicalVolume;
  G4VPhysicalVolume * ConcreteWallPhysicalVolume; 
  


  G4LogicalVolume * WaterSpaceLogicalVolume; 
  G4VPhysicalVolume * WaterSpacePhysicalVolume;   
  
    
  
  G4LogicalVolume * SteelWallLogicalVolume; 
  G4VPhysicalVolume * SteelWallPhysicalVolume; 
  
  G4LogicalVolume * AirLogicalVolume; 
  G4VPhysicalVolume * AirPhysicalVolume; 
  
  
  G4LogicalVolume * InAirWallLogicalVolume; 
  G4VPhysicalVolume * InAirWallPhysicalVolume; 
  
  
  G4LogicalVolume * OuterVesselLogicalVolume; 
  G4VPhysicalVolume * OuterVesselPhysicalVolume; 

  G4LogicalVolume * TestConcreteWallLogicalVolume; 
  G4VPhysicalVolume * TestConcreteWallPhysicalVolume; 

  G4LogicalVolume * TestSteelWallLogicalVolume; 
  G4VPhysicalVolume * TestSteelWallPhysicalVolume; 


  G4LogicalVolume * TestSideConcreteWallLogicalVolume; 
  G4VPhysicalVolume * TestSideConcreteWallPhysicalVolume; 

  G4LogicalVolume * TestSideSteelWallLogicalVolume; 
  G4VPhysicalVolume * TestSideSteelWallPhysicalVolume; 
  

};


#endif // PANDAXLAB_H

