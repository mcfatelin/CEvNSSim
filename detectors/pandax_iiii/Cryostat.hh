#ifndef CRYOSTAT_H
#define CRYOSTAT_H

#include "detector/BambooDetectorPart.hh"
#include "detector/BambooDetectorFactory.hh"

#include <vector>
using namespace std;

class Cryostat : public BambooDetectorPart
{

public:

  Cryostat(const G4String &name);
  virtual G4bool construct();
	static DetectorRegister<Cryostat> reg;

  G4bool ConstructOuterVessel();
  G4bool ConstructOuterVesselFlange();
  G4bool ConstructMiddleVessel();

  G4bool ConstructCryoVacuum();
  G4bool ConstructInnerVessel();
  G4bool ConstructCalibration();





private:

  G4LogicalVolume *m_pOuterVesselLogicalVolume;
  G4VPhysicalVolume *m_pOuterVesselPhysicalVolume;

  G4LogicalVolume *m_pOuterVesselFlangeLogicalVolume;
  G4VPhysicalVolume *m_pOuterVesselFlangePhysicalVolume;


  G4LogicalVolume *m_pCuOuterVesselLogicalVolume;
  G4VPhysicalVolume *m_pCuOuterVesselPhysicalVolume;

  G4LogicalVolume *m_pCuOuterVesselFlangeLogicalVolume;
  G4VPhysicalVolume *m_pCuOuterVesselFlangePhysicalVolume;

  G4LogicalVolume *m_pMiddleVesselLogicalVolume;
  G4VPhysicalVolume *m_pMiddleVesselPhysicalVolume;


  G4LogicalVolume *m_pCryoVacuumLogicalVolume;
  G4VPhysicalVolume *m_pCryoVacuumPhysicalVolume;

  G4LogicalVolume *m_pCalibrationSourceTubeLogicalVolume;
  G4VPhysicalVolume *m_pCalibrationSourceTubePhysicalVolume;

  G4LogicalVolume *m_pCalibrationSourceSSLogicalVolume;
  G4VPhysicalVolume *m_pCalibrationSourceSSPhysicalVolume;

  G4LogicalVolume *m_pCalibrationSourceLogicalVolume;
  G4VPhysicalVolume *m_pCalibrationSourcePhysicalVolume;


  G4LogicalVolume *m_pInnerVesselLogicalVolume;
  G4VPhysicalVolume *m_pInnerVesselPhysicalVolume;

  G4LogicalVolume *m_pInnerVesselFlangeLogicalVolume;

  G4LogicalVolume *m_pInnerVesselTopFlangeLogicalVolume;
 G4VPhysicalVolume *m_pInnerVesselTopFlangePhysicalVolume;

  G4LogicalVolume *m_pInnerVesselBottomFlangeLogicalVolume;
  G4VPhysicalVolume *m_pInnerVesselBottomFlangePhysicalVolume;



  G4LogicalVolume *m_pInnerVesselBoltScrewLogicalVolume;
  vector<G4VPhysicalVolume *> m_hInnerVesselTopBoltScrewPhysicalVolumes;
  vector<G4VPhysicalVolume *> m_hInnerVesselBottomBoltScrewPhysicalVolumes;









};


#endif // CRYOSTAT_H

