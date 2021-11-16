#ifndef XENONDETECTOR_H
#define XENONDETECTOR_H

#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4Ellipsoid.hh>
#include <G4UnionSolid.hh>
#include <G4Colour.hh>
#include <G4Polyhedra.hh>
#include <G4SubtractionSolid.hh>
#include <G4Box.hh>
#include <G4VisAttributes.hh>
#include <G4PVPlacement.hh>
#include <G4Polycone.hh>
#include <G4SDManager.hh>
#include <G4OpticalSurface.hh>
#include <G4SDParticleFilter.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>

#include "detector/BambooDetectorPart.hh"
#include "detector/BambooDetectorFactory.hh"
#include <vector>



class G4OpticalSurface;
using namespace std;

class XenonDetector : public BambooDetectorPart
{

public:

      XenonDetector(const G4String &name);

      virtual G4bool construct();

      static DetectorRegister<XenonDetector> reg;

      G4bool ConstructLaboratory();


      G4bool ConstructTPC();
      G4bool ConstructPMTArrays();
      G4bool ConstructElectrodes();

      G4bool DefineOpticalSurface();

      void GetSidePMTOffsetXY(G4int Index, G4double &pOffsetX, G4double &pOffsetY);

private:


    // ==============  logical volumes ====================
	G4LogicalVolume *m_pMotherLogicalVolume;




	// from top to bottom
	G4LogicalVolume *m_pTeflonCylinderLogicalVolume;


	G4LogicalVolume *m_pGXeSDLogicalVolume;
	G4LogicalVolume *m_pLXeSDLogicalVolume;

	//////////////////////////////////////////
	// for Qing
	//////////////////////////////////////////
	G4LogicalVolume* m_pLeadLayerLogicalVolume;
	G4LogicalVolume* m_pPELayerLogicalVolume;
	G4LogicalVolume* m_pCopperLayerLogicalVolume;
	G4LogicalVolume* m_pAirLayerLogicalVolume;
	G4LogicalVolume* m_pSSVesselLogicalVolume;
	G4LogicalVolume* m_pSSTopLogicalVolume;
	G4LogicalVolume* m_pSSBottomLogicalVolume;
	G4LogicalVolume* m_pLXeLogicalVolume;
	G4LogicalVolume* m_pTopPMTLogicalVolume;
	G4LogicalVolume* m_pBottomPMTLogicalVolume;


	//////////////////////////////////////////

	G4LogicalVolume *m_pPmtWindowLogicalVolume;
	G4LogicalVolume *m_pPmtCasingLogicalVolume;
	G4LogicalVolume *m_pPmtPhotoCathodeLogicalVolume;
	G4LogicalVolume *m_pPmtInteriorLogicalVolume;

	G4LogicalVolume *m_pBottomPMTWindowLogicalVolume;
	G4LogicalVolume *m_pBottomPMTPhotoCathodeLogicalVolume;

	// ============== finish logical volume ===============



    //============================
	// ===============  physical volumes ==============
    //============================
	G4VPhysicalVolume *m_pTeflonCylinderPhysicalVolume;

	G4VPhysicalVolume *m_pLXeSDPhysicalVolume;
	G4VPhysicalVolume *m_pGXeSDPhysicalVolume;

	//////////////////////////////////////////
	// for Qing
	//////////////////////////////////////////
	G4VPhysicalVolume* m_pLeadLayerPhysicalVolume;
	G4VPhysicalVolume* m_pPELayerPhysicalVolume;
	G4VPhysicalVolume* m_pCopperLayerPhysicalVolume;
	G4VPhysicalVolume* m_pAirLayerPhysicalVolume;
	G4VPhysicalVolume* m_pSSVesselPhysicalVolume;
	G4VPhysicalVolume* m_pSSTopPhysicalVolume;
	G4VPhysicalVolume* m_pSSBottomPhysicalVolume;
	G4VPhysicalVolume* m_pLXePhysicalVolume;
	G4VPhysicalVolume* m_pTopPMTPhysicalVolume;
	G4VPhysicalVolume* m_pBottomPMTPhysicalVolume;

	//////////////////////////////////////////

	vector<G4VPhysicalVolume *> m_pPmtWindowPhysicalVolume;
	vector<G4VPhysicalVolume *> m_pPmtCasingPhysicalVolume;
	G4VPhysicalVolume *m_pPmtInteriorPhysicalVolume;
	G4VPhysicalVolume *m_pPmtPhotoCathodePhysicalVolume;

	G4VPhysicalVolume *m_pBottomPMTPhotoCathodePhysicalVolume;
	G4VPhysicalVolume *m_pBottomPMTWindowPhysicalVolume;



	// ================ finish physical volumes ============


};


#endif // XENONDETECTOR_H

