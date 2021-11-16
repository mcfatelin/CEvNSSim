#include "detector/BambooDetectorPart.hh"
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>

#define DEBUG_DETPART

//#define SWITCH_PX2
//#define SWITCH_PX4

BambooDetectorPart::BambooDetectorPart(const G4String& partName)
	: partName_{ partName }, partLogicalVolume_{ 0 },
	partContainerLogicalVolume_{ 0 }, partPhysicalVolume_{ 0 }, parentPart_{ 0 } {}

void BambooDetectorPart::setParent(BambooDetectorPart* parent) {
	parentPart_ = parent;
}

G4LogicalVolume* BambooDetectorPart::getLogicalVolume() {
	return partLogicalVolume_;
}

G4VPhysicalVolume* BambooDetectorPart::getPhysicalVolume() {
	return partPhysicalVolume_;
}

G4LogicalVolume* BambooDetectorPart::getContainerLogicalVolume() {
	return partContainerLogicalVolume_;
}


void BambooDetectorPart::DefineGeometryParameters(const G4String value)
{
	//#ifdef SWITCH_PX4
		//DefineGeometryParametersPandaX4(value);
	//#endif
}

void BambooDetectorPart::DefineGeometryParametersPandaXSP(const G4String value)
{
	//================================== World =================================
	m_hGeometryParameters["WorldHeight"]			= 5.0*m;
	m_hGeometryParameters["WorldRadius"]			= 5.0*m;

	// ================================= Qing's part ===============================
	m_hGeometryParameters["LXeRadius"]              = 28.0/2.*cm;
	m_hGeometryParameters["LXeHeight"]              = 30.0*cm;
	m_hGeometryParameters["SSVesselRadius"]         = 20.0*cm; // not fixed
	m_hGeometryParameters["SSVesselHeight"]         = 80.0*cm; // not fixed
	m_hGeometryParameters["SSVesselThickness"]      = 3.0*cm; // oversized to be conservative
	m_hGeometryParameters["CavityWidth"]            = 65.0*cm;
	m_hGeometryParameters["CavityHeight"]           = 120.0*cm;
	m_hGeometryParameters["CopperThickness"]        = 3.0*cm;
	m_hGeometryParameters["PEThickness"]            = 80.0*cm;
	m_hGeometryParameters["LeadThickness"]          = 15.0*cm;

	// derivced
	m_hGeometryParameters["CopperWidth"]            = GetGeometryParameter("CavityWidth") + 2.0*GetGeometryParameter("CopperThickness");
	m_hGeometryParameters["CopperHeight"]           = GetGeometryParameter("CavityHeight")+2.0*GetGeometryParameter("CopperThickness");
	m_hGeometryParameters["PEWidth"]                = GetGeometryParameter("CopperWidth") + 2.0*GetGeometryParameter("PEThickness");
	m_hGeometryParameters["PEHeight"]               = GetGeometryParameter("CopperHeight") + 2.0*GetGeometryParameter("PEThickness");
	m_hGeometryParameters["LeadWidth"]              = GetGeometryParameter("PEWidth") + 2.0*GetGeometryParameter("LeadThickness");
	m_hGeometryParameters["LeadHeight"]             = GetGeometryParameter("PEHeight") + 2.0*GetGeometryParameter("LeadThickness");

	// placeholder PMT parameters
	m_hGeometryParameters["PMTWidth"]               = 25.6*mm;
	m_hGeometryParameters["PMTThickness"]           = 0.01*mm;

//
//
//    //=================================== Outer Copper Vessel inside laboratory (tube block) ===============
//    m_hGeometryParameters["OuterVesselFlangeDiameter"] = 289.6*mm;
//    m_hGeometryParameters["OuterVesselFlangeThickness"] = 26.5*mm;
//    m_hGeometryParameters["OuterVesselTubeOuterRadius"] = 254.0 / 2. *mm ;
//    m_hGeometryParameters["OuterVesselTubeThickness"] = 3.2*mm;
//    m_hGeometryParameters["OuterVesselTubeInnerRadius"] = GetGeometryParameter("OuterVesselTubeOuterRadius") - GetGeometryParameter("OuterVesselTubeThickness");
//    m_hGeometryParameters["OuterVesselTubeHeight"] = 457.2*mm;
//	m_hGeometryParameters["OuterVesselTubeZshift"] = 0.0 *mm;
//
//    //===================================  Vacuum volume=========
//    // inner titanium vessel is inside this vacuum volume
//    m_hGeometryParameters["CryoVacuumHeight"] = GetGeometryParameter("OuterVesseTubelHeight");
//    m_hGeometryParameters["CryoVacuumOuterRadius"] = GetGeometryParameter("OuterVesselTubeInnerRadius");
//    m_hGeometryParameters["CryoVacuumZshift"]=0.0;
//
//
//    //==================== Inner Vessel ====
//    m_hGeometryParameters["InnerVesselFlangeDiameter"] = 203.2*mm;
//    m_hGeometryParameters["InnerVesselFlangeThickness"] = 22.4*mm; // two flanges each side
//    m_hGeometryParameters["InnerVesselTubeThickness"] = 2.6*mm;
//    m_hGeometryParameters["InnerVesselTubeOuterRadius"] = 76.5*mm;
//    m_hGeometryParameters["InnerVesselTubeInnerRadius"] = GetGeometryParameter("InnerVesselTubeOuterRadius") - GetGeometryParameter("InnerVesselTubeThickness");
//    m_hGeometryParameters["InnerVesselTubeHeight"] = 304.8*mm;
//    m_hGeometryParameters["InnerVesselTubeZshift"] = 0.0 * mm;
//
//	//==================== Source box ===============
//	m_hGeometryParameters["SourceBoxWidth"] = 50.0*mm;
//	m_hGeometryParameters["SourceBoxZshift"] = 35.1*mm;
//	m_hGeometryParameters["SourceBoxYshift"] = GetGeometryParameter("OuterVesselTubeOuterRadius") + GetGeometryParameter("SourceBoxWidth") / 2. + 10.0*mm;
//	m_hGeometryParameters["CutoffSphereRadius"] = 2.0*mm;
//	m_hGeometryParameters["OutTubeRadius"] = 1.0*mm;
//
//
//	// ================  Teflon block ==============
//	m_hGeometryParameters["TeflonBlockOuterRadius"] = (1500. + 25.) *mm; //for single phase
//	m_hGeometryParameters["TeflonBlockInnerRadius"] = (1500. + 5) *mm; // for single phase
//	m_hGeometryParameters["TeflonBlockHeight"]      = 3000. *mm; // for single phase
////	m_hGeometryParameters["TeflonBlockOuterRadius"] = (100. + 25.) *mm; //for single phase 10cm for debug
////	m_hGeometryParameters["TeflonBlockInnerRadius"] = (100. + 5) *mm; // for single phase 10cm for debug
////	m_hGeometryParameters["TeflonBlockHeight"]      = 300. *mm; // for single phase 10cm for debug
//	m_hGeometryParameters["TeflonBlockHeightType1"] = 5.0*mm;
//	m_hGeometryParameters["TeflonBlockHeightType2"] = 10.0*mm;
////	m_hGeometryParameters["TeflonBlockNumber"]      = 18; // for single phase
//
//    m_hGeometryParameters["NumberOfSidePMTs"]       = 1681; // for single phase, side PMT number on each side, sqrt of it shall be an integer
//    m_hGeometryParameters["SidePMTDistance"]        = 25.4*mm; // for single phase
//	m_hGeometryParameters["LightSensorWidth"]       = 25.4*mm; // for single phase
//	m_hGeometryParameters["WindowWidth"]            = 25.4*mm; // for single phase; window and photo-cathode sizes are the same just a bit smaller than whole light sensor casing
//	m_hGeometryParameters["LightSensorThickness"]   = 3.0*mm; // for single phase
//	m_hGeometryParameters["PhotoCathodeThickness"]  = 0.5*mm; // for single phase
//	m_hGeometryParameters["WindowThickness"]        = 1.5*mm; // for single phase
//	m_hGeometryParameters["LightSensorCoverage"]    = 0.5; // for single phase; This is nominal value, actually value will be slightly different
//
//	// ================= Top/Bottom cap for single phase ================
//	m_hGeometryParameters["TopBottomCapThickness"]  = 10.0*mm;
//
//	// ================= LXe volume height and radius =================
//	m_hGeometryParameters["LXeRadius"]      = 0.5*(GetGeometryParameter("TeflonBlockOuterRadius") + GetGeometryParameter("WorldRadius"));
//	m_hGeometryParameters["LXeHeight"]      = 0.5*(GetGeometryParameter("TeflonBlockHeight") + GetGeometryParameter("WorldHeight"));
//
//
//	// ================ Teflon holder ================
//	m_hGeometryParameters["TeflonHolderOuterRadius"] = 100.0 / 2.  * mm;
//	m_hGeometryParameters["TeflonHolderInnerRadius"] = 57.0 / 2. *mm;
//	m_hGeometryParameters["TeflonHolderHeight"] = 10.0*mm;
//
//	// ================ Peek supporter ================
//	m_hGeometryParameters["PeekSupporterDiameter"] = 6.0 * mm;
//	m_hGeometryParameters["PeekSupporterLengthType1"] = 220.0*mm; //upper one
//	m_hGeometryParameters["PeekSupporterLengthType2"] = 50.0 *mm; // lower one
//	m_hGeometryParameters["PeekSupporterZshiftType1"] = GetGeometryParameter("InnerVesselTubeHeight") / 2. - GetGeometryParameter("PeekSupporterLengthType1") / 2.;
//	m_hGeometryParameters["PeekSupporterZshiftType2"] = GetGeometryParameter("InnerVesselTubeHeight") / 2. - GetGeometryParameter("PeekSupporterLengthType1") - GetGeometryParameter("PeekSupporterLengthType2") / 2.;
//	m_hGeometryParameters["PeekSupporterRshiftType1"] = 90.0 * mm;
//	m_hGeometryParameters["PeekSupporterRshiftType2"] = 67.0 * mm;
//
//	// ================= Electrode(not necessary in simple version) ==================
//	m_hGeometryParameters["ElectrodeOuterRadius"] = GetGeometryParameter("TeflonBlockOuterRadius");
//	m_hGeometryParameters["ElectrodeInnerRadius"] = GetGeometryParameter("TeflonBlockInnerRadius");
//	m_hGeometryParameters["ElectrodeThickness"] = 1.0 * mm;
//
//	// ================== Teflon In GXe ==================
//	m_hGeometryParameters["TeflonBlockThicknessInGXe"]=12.0 * mm;
//	m_hGeometryParameters["TeflonBlock2ThicknessInGXe"]=2.5 * mm;
//
//	// ================== TPC structure in LXe ============
//	m_hGeometryParameters["TeflonBlockThicknessInLXe"]= (2.5 + 15.0) * mm;
//	m_hGeometryParameters["SSPlateWidthInLXe"] = 87.0 * mm;
//	m_hGeometryParameters["TeflonRingOuterRadius"] = GetGeometryParameter("TeflonHolderInnerRadius") + 1.0*mm;
//	m_hGeometryParameters["SSPlateThicknessInLXe"]=2.0*mm;
//	m_hGeometryParameters["TeflonBlock2ThicknessInLXe"]=10.0*mm;
//
//    //====================Liquid Level (changable)=============
//	m_hGeometryParameters["LiquidLevelFromBottom"] = 195.0 * mm;// measured in lab
//
//	m_hGeometryParameters["TeflonBottomBlockZshift"] = -GetGeometryParameter("InnerVesselTubeHeight") / 2. + GetGeometryParameter("LiquidLevelFromBottom") + 2.5*mm - GetGeometryParameter("TeflonBlockHeightType1") - GetGeometryParameter("ElectrodeThickness") - 2.*GetGeometryParameter("TeflonBlockHeightType2") - 2.*GetGeometryParameter("ElectrodeThickness") - GetGeometryParameter("TeflonBlockHeightType1") / 2.;
//
//	//==================== Electrode definition(added @ 2013-07-22) ==================
//	m_hGeometryParameters["MeshHoleWidth"] = 2.0*mm;
//	m_hGeometryParameters["MeshHoleSpacing"] = 2.0*mm;
//	//m_hGeometryParameters["MeshHoleSpacing"] = 5*mm;
//	m_hGeometryParameters["MeshThickness"] = 0.1*mm;
//	m_hGeometryParameters["MeshFrameWidth"] = 70.0*mm;
//	m_hGeometryParameters["MeshWireWidth"] = 0.1*mm;
//
//	m_hGeometryParameters["HexagonMeshHoleWidth"] = 7.8845*mm;
//	m_hGeometryParameters["HexagonMeshHoleXSpacing"] = 13.8564*mm;
//	m_hGeometryParameters["HexagonMeshHoleYSpacing"] = 16.0*mm;
//	m_hGeometryParameters["HexagonMeshThickness"] = 0.1*mm;
//	m_hGeometryParameters["HexagonMeshFrameWidth"] = 100.0*mm;
//
//	// for single phase
//	m_hGeometryParameters["WireDiameter"]           = 0.2*mm;
////	m_hGeometryParameters["CathodeWireNumber"]     = 450;
//	m_hGeometryParameters["CathodeWireNumber"]     = 36; //10-cm radius GS-TPC
//	m_hGeometryParameters["CathodeWireRadius"]      = 100.0*mm; // for single phase
//	m_hGeometryParameters["GateWireNumber"]        = 12;
//	m_hGeometryParameters["GateWireRadius"]         = 5.0*mm;
//
//	// ==================== SD LXe and GXe ==============
//	m_hGeometryParameters["LXeSDHeight"] = GetGeometryParameter("TeflonBlockThicknessInLXe") + GetGeometryParameter("SSPlateThicknessInLXe") + GetGeometryParameter("TeflonBlock2ThicknessInLXe");
//	m_hGeometryParameters["GXeSDHeight"] = GetGeometryParameter("TeflonBlockThicknessInGXe") + GetGeometryParameter("TeflonBlock2ThicknessInGXe");
//	m_hGeometryParameters["DriftRegionLength"]=10.0*mm;
//	m_hGeometryParameters["ScreenMeshToBottomPMTWindow"]=5.0*mm;
//	m_hGeometryParameters["AnodeToLiquidSurface"]=2.5*mm;
//	m_hGeometryParameters["GateMeshToLiquidSurface"]=2.5*mm;
//
//	m_hGeometryParameters["AnodeZoffset"] = -GetGeometryParameter("GXeSDHeight")/2. + GetGeometryParameter("AnodeToLiquidSurface");
//	m_hGeometryParameters["GateMeshZoffset"] = GetGeometryParameter("LXeSDHeight")/2. - GetGeometryParameter("GateMeshToLiquidSurface");
//	m_hGeometryParameters["CathodeZoffset"] = GetGeometryParameter("GateMeshZoffset") - GetGeometryParameter("DriftRegionLength");
//
//	//====================Level meter and outcome gas tube ===================
//	m_hGeometryParameters["LevelMeterLength"] = 200.0 * mm;
//	m_hGeometryParameters["LevelMeterOuterRadius"] = 3.2*mm;
//	m_hGeometryParameters["LevelMeterInnerRadius"] = 2.2*mm;
//	m_hGeometryParameters["LevelMeterZshift"] = - GetGeometryParameter("InnerVesselTubeHeight") / 2. + 18.0*mm + GetGeometryParameter("LevelMeterLength") / 2.;
//
//	m_hGeometryParameters["OutcomeTubeLength"] = GetGeometryParameter("InnerVesselTubeHeight") - 30.0*mm;
//	m_hGeometryParameters["OutcomeTubeOuterRadius"] = 3.2*mm;
//	m_hGeometryParameters["OutcomeTubeInnerRadius"] = 2.2*mm;
//	m_hGeometryParameters["OutcomeTubeZshift"] = GetGeometryParameter("InnerVesselTubeHeight") / 2. - GetGeometryParameter("OutcomeTubeLength") / 2.;
//
//	m_hGeometryParameters["LevelMeterRshift"] = 120.0*mm;
//
//
//
//
//	//============ Top PMTs =====================================
//	// pmts
//	m_hGeometryParameters["PmtWidth"]                 = 25.4*mm;
//	m_hGeometryParameters["PmtSpacing"]               = 2.03*mm;
//	m_hGeometryParameters["PmtWindowWidth"]           = 25.40*mm;
//	m_hGeometryParameters["PmtWindowThickness"]       = 1.50*mm;
//	m_hGeometryParameters["PmtCasingWidth"]           = 25.40*mm;
//	m_hGeometryParameters["PmtCasingHeight"]          = 27.00*mm;
//	m_hGeometryParameters["PmtCasingThickness"]       = 0.50*mm;
//	m_hGeometryParameters["PmtPhotoCathodeWidth"]     = 22.00*mm;
//	m_hGeometryParameters["PmtPhotoCathodeThickness"] = 0.50*mm;
//	m_hGeometryParameters["PmtBaseThickness"]         = 1.50*mm;
//	m_hGeometryParameters["PmtToPmtBase"]             = 3.00*mm;
//	m_hGeometryParameters["PmtBaseSpacerHeight"]      = 6.00*mm;
//
//
//	m_hGeometryParameters["PmtXshift"] = 26.7 / 2. * mm;
//	//m_hGeometryParameters["PmtWindowZshift"] = -0.5*GetGeometryParameter("InnerVesselTubeHeight")+0.5*GetGeometryParameter("LiquidLevelFromBottom") + GetGeometryParameter("TeflonBlockThicknessInGXe") + GetGeometryParameter("TeflonBlock2ThicknessInGXe")+GetGeometryParameter("PmtWindowThickness") /2. ;
//	//m_hGeometryParameters["PmtCasingZshift"] =  -0.5*GetGeometryParameter("InnerVesselTubeHeight")+0.5*GetGeometryParameter("LiquidLevelFromBottom") + GetGeometryParameter("TeflonBlockThicknessInGXe") + GetGeometryParameter("TeflonBlock2ThicknessInGXe")+GetGeometryParameter("PmtWindowThickness")+ GetGeometryParameter("PmtCasingHeight") / 2.;
//	m_hGeometryParameters["PmtWindowZshift"] = 0.5*GetGeometryParameter("LXeSDHeight")+0.5*GetGeometryParameter("GXeSDHeight")+0.5*GetGeometryParameter("PmtWindowThickness");
//	m_hGeometryParameters["PmtCasingZshift"] = 0.5*GetGeometryParameter("LXeSDHeight")+0.5*GetGeometryParameter("GXeSDHeight")+GetGeometryParameter("PmtWindowThickness") + 0.5*GetGeometryParameter("PmtCasingHeight");
//
//	m_hGeometryParameters["NbTopPmts"] = 1;
//	m_hGeometryParameters["NbBottomPmts"] = 0;
//
//
//	//==================== Bottom PMT ====================
//    m_hGeometryParameters["R3PmtWindowDiameter"] 		= 77.0*mm;
//    m_hGeometryParameters["R3PmtWindowThickness"] 		= 1.5*mm;
//    m_hGeometryParameters["R3PmtCathodeDiameter"] 		= 64.0*mm;
//    m_hGeometryParameters["R3PmtCathodeThickness"]		= 0.5*mm;
}

void BambooDetectorPart::DefineGeometryParametersPandaX4(const G4String value)
{

#ifdef DEBUG_DETPART
	G4cout << "***DEBUG***: loaded - BambooDetectorPart::DefineGeometryParameters()" << G4endl;
#endif
	//======================================= Critical Parameters ===================================//

	m_hGeometryParameters["TestModelHandZShift"] = 0 * m;
	m_hGeometryParameters["TestSideModelHandXShift"] = 0 * m;
	m_hGeometryParameters["TestModelThickness"] = 30 * mm;
	m_hGeometryParameters["TestSideModelThickness"] = 30 * mm;

	//the important parameters

	m_hGeometryParameters["DetectorZShift"] = 0 * m;
	m_hGeometryParameters["ShieldSpace"] = 75 * mm; //the distance from the innervesselinnerradius to the innerptfeinnerradius
	m_hGeometryParameters["VacuumShieldSpace"] = 100 * mm; //the distance from the innervesselinnerradius to the innerptfeinnerradius
	m_hGeometryParameters["OuterVesselInnerVesselHandZShift"] = 0 * m; // the distance between bottom edge of outervessel barrel and bottom edge of innervessel barrel

  // for cubarrel

	m_hGeometryParameters["InnerVesselOriginThickness"] = 6 * mm;
	m_hGeometryParameters["CopperInsertionThickness"] = 10 * mm;
	m_hGeometryParameters["InnerVesselThickness"] = GetGeometryParameter("InnerVesselOriginThickness");//6mm


	// important parameters!!!

	m_hGeometryParameters["InnerVesselDomeThickness"] = GetGeometryParameter("InnerVesselThickness");
	m_hGeometryParameters["CopperInsertionDomeThickness"] = GetGeometryParameter("CopperInsertionThickness");
	m_hGeometryParameters["CathodeToGate"] = 1185 * mm;
	m_hGeometryParameters["NumSides"] = 24;
	m_hGeometryParameters["InnerVesselFlangeHeight"] = 200 * mm;
	m_hGeometryParameters["InnerVesselFlangeThickness"] = 80 * mm;
	m_hGeometryParameters["OuterVesselThickness"] = 10 * mm;//-----171126modified
	m_hGeometryParameters["OuterVesselFlangeHeight"] = 200 * mm;
	m_hGeometryParameters["OuterVesselFlangeThickness"] = 100 * mm;
	m_hGeometryParameters["CryoVacuumRadius"] = 1.7 * m / 2;//-----171126modified
	m_hGeometryParameters["CryoVacuumHeight"] = 2.2 * m;
	m_hGeometryParameters["MiddleVesselThickness"] = 5 * mm;

	//the second important parameters, usually these parameters are fixed

	m_hGeometryParameters["InnerPTFEInnerRadius"] = GetGeometryParameter("CathodeToGate") / 2;//592.5mm

	m_hGeometryParameters["TopSpace"] = 400 * mm;//300*mm;//155*mm;-----180119modified//-----180122modified
	m_hGeometryParameters["BottomSpace"] = 155 * mm;//180119TBD

	m_hGeometryParameters["GateToSurface"] = 5.5 * mm;
	m_hGeometryParameters["AnodeToSurface"] = 5.5 * mm;
	m_hGeometryParameters["ScreenToBottomPTFE"] = 5 * mm;
	m_hGeometryParameters["GateToTopPMT"] = 50.5 * mm;//-----180119modified

	m_hGeometryParameters["NbShapingRings"] = 58;//-----180119modified
	m_hGeometryParameters["InnerVesselBoltScrewTotalNumber"] = GetGeometryParameter("NumSides") * 1.5;

	m_hGeometryParameters["CuPlateThickness"] = 20 * mm;//-----171126modified
	m_hGeometryParameters["PTFEPlateThickness"] = 6 * mm;
	m_hGeometryParameters["HalfDistance"] = 90.8 * mm;//-----180119modified
	m_hGeometryParameters["InnerPTFEThickness"] = 6 * mm;
	m_hGeometryParameters["RibandInnerPTFEHolderThickness"] = 25. * mm;//-------180204modified

	m_hGeometryParameters["DistanceCuPlateToInnerVessel"] = 5 * mm;//-----171126modified

  // deductive Distance

	m_hGeometryParameters["SurfaceToTopPMT"] = //45mm
		GetGeometryParameter("GateToTopPMT") //50.5mm
		- GetGeometryParameter("GateToSurface");//5.5mm
	m_hGeometryParameters["SurfaceToBottomPMT"] = //1281.3mm
		GetGeometryParameter("GateToSurface") //5.5mm
		+ GetGeometryParameter("CathodeToGate") //1185mm
		+ GetGeometryParameter("HalfDistance");//90.8mm
	m_hGeometryParameters["DistanceTop"] = //426mm
		GetGeometryParameter("CuPlateThickness") //20mm
		+ GetGeometryParameter("PTFEPlateThickness") //6mm
		+ GetGeometryParameter("TopSpace");//400mm
	m_hGeometryParameters["DistanceBottom"] = //181mm
		GetGeometryParameter("CuPlateThickness") //20mm
		+ GetGeometryParameter("PTFEPlateThickness") //6mm
		+ GetGeometryParameter("BottomSpace");//155mm

	// other parameters

	m_hGeometryParameters["OuterVesselHeight"] = GetGeometryParameter("CryoVacuumHeight");
	m_hGeometryParameters["InnerVesselInnerRadius"] = //667.5mm
		GetGeometryParameter("InnerPTFEInnerRadius") //592.5mm
		+ GetGeometryParameter("ShieldSpace");//75mm
	m_hGeometryParameters["InnerVesselOuterRadius"] = //673.5mm
		GetGeometryParameter("InnerVesselInnerRadius") //667.5mm
		+ GetGeometryParameter("InnerVesselThickness");//6mm
	m_hGeometryParameters["InnerVesselBarrelHeight"] = //1933.3mm
		GetGeometryParameter("SurfaceToBottomPMT") //1281.3mm
		+ GetGeometryParameter("SurfaceToTopPMT") //45mm
		+ GetGeometryParameter("DistanceTop") //426mm
		+ GetGeometryParameter("DistanceBottom");//181mm

	m_hGeometryParameters["BottomInsertHeight"] = GetGeometryParameter("BottomSpace");
	m_hGeometryParameters["OuterVesselInnerVesselZShift"] = //133.35mm
		GetGeometryParameter("CryoVacuumHeight") / 2 //2200mm/2
		- GetGeometryParameter("InnerVesselBarrelHeight") / 2 //1933.3mm/2
		+ GetGeometryParameter("OuterVesselInnerVesselHandZShift");//0mm

	// ===============  the following are deductive parameters or some other not important parameters=================

	//===================================== CryoVacuum =================================

	m_hGeometryParameters["CryoVacuumDomeRadius"] = 2 * GetGeometryParameter("CryoVacuumRadius");

	m_hGeometryParameters["CryoVacuumDomeHeight"] = GetGeometryParameter("CryoVacuumDomeRadius") - sqrt(GetGeometryParameter("CryoVacuumDomeRadius") * GetGeometryParameter("CryoVacuumDomeRadius") - GetGeometryParameter("CryoVacuumRadius") * GetGeometryParameter("CryoVacuumRadius"));

	//===================================== OuterVessel =================================

	m_hGeometryParameters["OuterVesselInnerRadius"] = GetGeometryParameter("CryoVacuumRadius");
	m_hGeometryParameters["OuterVesselOuterRadius"] = GetGeometryParameter("CryoVacuumRadius") + GetGeometryParameter("OuterVesselThickness");

	m_hGeometryParameters["OuterVesselOuterDomeRadius"] = 2 * GetGeometryParameter("OuterVesselOuterRadius");

	m_hGeometryParameters["OuterVesselOuterDomeHeight"] = GetGeometryParameter("OuterVesselOuterDomeRadius") - sqrt(GetGeometryParameter("OuterVesselOuterDomeRadius") * GetGeometryParameter("OuterVesselOuterDomeRadius") - GetGeometryParameter("OuterVesselOuterRadius") * GetGeometryParameter("OuterVesselOuterRadius"));

	//======================================= MiddleVessel =================================

	m_hGeometryParameters["MiddleVesselOuterRadius"] = GetGeometryParameter("OuterVesselInnerRadius");
	m_hGeometryParameters["MiddleVesselInnerRadius"] = GetGeometryParameter("MiddleVesselOuterRadius") - GetGeometryParameter("MiddleVesselThickness");
	m_hGeometryParameters["MiddleVesselZShift"] = GetGeometryParameter("DetectorZShift");

	m_hGeometryParameters["MiddleVesselHeight"] = GetGeometryParameter("CryoVacuumHeight");

	//==================================  OuterVessel Flange ================================================//

	m_hGeometryParameters["OuterVesselFlangeInnerRadius"] = GetGeometryParameter("OuterVesselOuterRadius");
	m_hGeometryParameters["OuterVesselFlangeOuterRadius"] = GetGeometryParameter("OuterVesselFlangeInnerRadius") + GetGeometryParameter("OuterVesselFlangeThickness");
	m_hGeometryParameters["OuterVesselFlangeZShift"] = GetGeometryParameter("OuterVesselHeight") / 2 - GetGeometryParameter("OuterVesselFlangeHeight") / 2;

	//==========================================  Calibration =================================================//

	m_hGeometryParameters["CalibrationSourceTubeInnerRadius"] = 10.0 * mm * 0.5;
	m_hGeometryParameters["CalibrationSourceTubeOuterRadius"] = 14.0 * mm * 0.5;
	m_hGeometryParameters["CalibrationSourceTubeTorusRadius"] = GetGeometryParameter("CryoVacuumRadius") - GetGeometryParameter("CalibrationSourceTubeOuterRadius");

	m_hGeometryParameters["CalibrationSourceTubeInnerRadius"] = 10.0 * mm * 0.5;
	m_hGeometryParameters["CalibrationSourceTubeOuterRadius"] = 14.0 * mm * 0.5;
	m_hGeometryParameters["CalibrationSourceTubeTorusRadius"] = GetGeometryParameter("CryoVacuumRadius") - GetGeometryParameter("CalibrationSourceTubeOuterRadius");

	m_hGeometryParameters["CalibrationSourceSSXpos"] = GetGeometryParameter("CalibrationSourceTubeTorusRadius") * cos(GetGeometryParameter("CalibrationSourceSSPhiOffset"));
	m_hGeometryParameters["CalibrationSourceSSYpos"] = GetGeometryParameter("CalibrationSourceTubeTorusRadius") * sin(GetGeometryParameter("CalibrationSourceSSPhiOffset"));
	m_hGeometryParameters["CalibrationSourceSSZshift"] = 136.381 * mm;

	m_hGeometryParameters["CalibrationSourceRadius"] = 2.0 * mm;
	m_hGeometryParameters["CalibrationSourceHeight"] = 2.0 * mm;
	m_hGeometryParameters["CalibrationSourceToSSZshift"] = -2.0 * mm;

	m_hGeometryParameters["CalibrationSourceSSRadius"] = 3.0 * mm;
	m_hGeometryParameters["CalibrationSourceSSHeight"] = 10.0 * mm;
	m_hGeometryParameters["CalibrationSourceSSPhiOffset"] = 270.0 * deg + 135.0 * deg;

	//================================== InnerVessel =================================

	m_hGeometryParameters["InnerVesselBarrelInnerRadius"] = GetGeometryParameter("InnerVesselInnerRadius");//667.5mm
	m_hGeometryParameters["InnerVesselBarrelOuterRadius"] = GetGeometryParameter("InnerVesselOuterRadius");//673.5mm
	m_hGeometryParameters["InnerVesselDomeInnerRadius"] = 2 * GetGeometryParameter("InnerVesselInnerRadius");//667.5mm*2=1335mm
	m_hGeometryParameters["InnerVesselDomeOuterRadius"] = 2 * GetGeometryParameter("InnerVesselOuterRadius");//673.5mm*2=1347mm

	m_hGeometryParameters["InnerVesselDomeOuterHeight"] = //180.46378mm
		GetGeometryParameter("InnerVesselDomeOuterRadius") //1347mm
		- sqrt(
			GetGeometryParameter("InnerVesselDomeOuterRadius") //1347mm
			* GetGeometryParameter("InnerVesselDomeOuterRadius") //1347mm
			- GetGeometryParameter("InnerVesselOuterRadius") //673.5mm
			* GetGeometryParameter("InnerVesselOuterRadius"));//673.5mm
	m_hGeometryParameters["InnerVesselDomeInnerHeight"] = //178.85609mm
		GetGeometryParameter("InnerVesselDomeInnerRadius") //1335mm
		- sqrt(
			GetGeometryParameter("InnerVesselDomeInnerRadius") //1335mm
			* GetGeometryParameter("InnerVesselDomeInnerRadius") //1335mm
			- GetGeometryParameter("InnerVesselInnerRadius") //667.5mm
			* GetGeometryParameter("InnerVesselInnerRadius")//667.5mm
		);
	m_hGeometryParameters["InnerVesselZShift"] = -GetGeometryParameter("OuterVesselInnerVesselZShift");

	//================================== InnerVessel Flange ============================================//

	m_hGeometryParameters["InnerVesselFlangeInnerRadius"] = GetGeometryParameter("InnerVesselOuterRadius");//1347mm
	m_hGeometryParameters["InnerVesselFlangeOuterRadius"] = GetGeometryParameter("InnerVesselFlangeInnerRadius") + GetGeometryParameter("InnerVesselFlangeThickness");
	m_hGeometryParameters["InnerVesselFlangeZshift"] = -GetGeometryParameter("InnerVesselFlangeHeight") / 2 + GetGeometryParameter("InnerVesselBarrelHeight") / 2 - GetGeometryParameter("OuterVesselInnerVesselZShift");

	//=========================================  BoltScrew ===================================//

	m_hGeometryParameters["InnerVesselBoltHeight"] = 10.0 * mm;
	m_hGeometryParameters["InnerVesselBoltRadius"] = 15.0 * mm;
	m_hGeometryParameters["InnerVesselScrewRadius"] = 10.0 * mm;

	m_hGeometryParameters["InnerVesselScrewHeight"] = GetGeometryParameter("InnerVesselFlangeHeight");
	m_hGeometryParameters["InnerVesselBoltScrewHeight"] = GetGeometryParameter("InnerVesselScrewHeight") + GetGeometryParameter("InnerVesselBoltHeight") * 2.0;
	m_hGeometryParameters["InnerVesselBoltScrewZshift"] = GetGeometryParameter("InnerVesselFlangeZshift") - GetGeometryParameter("InnerVesselBoltScrewHeight") / 2.0;


	//======================================   LXe, GXe   ====================================//


	m_hGeometryParameters["GXeHeight"] = //471mm
		GetGeometryParameter("SurfaceToTopPMT") //45mm
		+ GetGeometryParameter("DistanceTop");//426mm

	m_hGeometryParameters["LXeHeight"] = //1462mm
		GetGeometryParameter("SurfaceToBottomPMT") //1281.3mm
		+ GetGeometryParameter("DistanceBottom");//181mm

	m_hGeometryParameters["LXeZshift"] = //189.5mm
		GetGeometryParameter("InnerVesselDomeInnerRadius") //1335mm
		- GetGeometryParameter("InnerVesselBarrelHeight") / 2.0 //1933.3mm/2
		- GetGeometryParameter("InnerVesselDomeInnerHeight"); //178.85609mm
	m_hGeometryParameters["GXeZshift"] = GetGeometryParameter("LXeZshift");


	//============================LXeSD and GXeSD ==========================================//

	m_hGeometryParameters["LXeHSDHeight"] = GetGeometryParameter("HalfDistance");//90.8mm


	m_hGeometryParameters["LXeSDHeight"] = 
		GetGeometryParameter("CathodeToGate") 
		+ GetGeometryParameter("GateToSurface");//1185+5.5=1190.5mm

	m_hGeometryParameters["GXeSDHeight"] = GetGeometryParameter("SurfaceToTopPMT");//45mm

	m_hGeometryParameters["GXeSkinSDHeight"] = GetGeometryParameter("GXeSDHeight");
	m_hGeometryParameters["LXeSkinSDHeight"] = GetGeometryParameter("SurfaceToBottomPMT");


	m_hGeometryParameters["LXeSDZshift"] = //-694.85mm
		-GetGeometryParameter("InnerVesselBarrelHeight") / 2 //1933.3/2=966.65mm
		+ GetGeometryParameter("DistanceBottom") //181mm
		+ GetGeometryParameter("LXeHSDHeight");//90.8mm

	m_hGeometryParameters["LXeHSDZshift"] = -GetGeometryParameter("InnerVesselBarrelHeight") / 2 + GetGeometryParameter("DistanceBottom");

	m_hGeometryParameters["GXeSDZshift"] = 0 - GetGeometryParameter("GXeHeight") / 2;//0-471/2=-235.5mm
	m_hGeometryParameters["GXeSkinSDZshift"] = 0 - GetGeometryParameter("GXeHeight") / 2 + GetGeometryParameter("GXeSDHeight") / 2;
	m_hGeometryParameters["LXeSkinSDZshift"] = 0 - GetGeometryParameter("InnerVesselBarrelHeight") / 2 + GetGeometryParameter("DistanceBottom") + GetGeometryParameter("LXeSkinSDHeight") / 2;//180119modified

 //=====================================Inner PTFE ==========================================//

	m_hGeometryParameters["InnerPTFEOuterRadius"] = GetGeometryParameter("InnerPTFEInnerRadius") + GetGeometryParameter("InnerPTFEThickness");
	m_hGeometryParameters["SidePTFEHeightTop"] = GetGeometryParameter("SurfaceToTopPMT");
	m_hGeometryParameters["SidePTFEHeightBottom"] = GetGeometryParameter("SurfaceToBottomPMT");
	m_hGeometryParameters["InnerPTFETopZshift"] = 0 - GetGeometryParameter("GXeHeight") / 2;
	m_hGeometryParameters["InnerPTFEZshift"] = 0 - GetGeometryParameter("InnerVesselBarrelHeight") / 2 + GetGeometryParameter("DistanceBottom");


	//================================== Cu plate  ===========================================//

	m_hGeometryParameters["CuPlateRadius"] = GetGeometryParameter("InnerVesselInnerRadius") - GetGeometryParameter("DistanceCuPlateToInnerVessel");

	m_hGeometryParameters["PTFEPlateRadius"] = GetGeometryParameter("InnerPTFEOuterRadius");

	m_hGeometryParameters["TopPTFEPlateZShift"] = 
		0 - GetGeometryParameter("GXeHeight") / 2 //471mm/2
		+ GetGeometryParameter("GXeSDHeight") 
		+ GetGeometryParameter("PTFEPlateThickness") / 2;

	m_hGeometryParameters["TopCuPlateZShift"] = 
		GetGeometryParameter("TopPTFEPlateZShift") 
		+ GetGeometryParameter("CuPlateThickness") / 2 
		+ GetGeometryParameter("PTFEPlateThickness") / 2;

	m_hGeometryParameters["BottomPTFEPlateZShift"] = //-788.65mm
		0 - GetGeometryParameter("InnerVesselBarrelHeight") / 2 //1933.3mm/2
		- GetGeometryParameter("PTFEPlateThickness") / 2 //6mm/2
		+ GetGeometryParameter("DistanceBottom");//181mm

	m_hGeometryParameters["BottomCuPlateZShift"] = GetGeometryParameter("BottomPTFEPlateZShift") - GetGeometryParameter("CuPlateThickness") / 2 - GetGeometryParameter("PTFEPlateThickness") / 2;


	//================================== mesh and mesh holder  =================================  

	m_hGeometryParameters["MeshThickness"] = 0.2 * mm;//-----171126modified
	m_hGeometryParameters["MeshRadius"] = GetGeometryParameter("InnerPTFEInnerRadius");

	m_hGeometryParameters["MeshHolderHeight"] = 11. * mm;//-----180122modified
	m_hGeometryParameters["MeshHolderThickness"] = 19.5 * mm;//20.*mm;//-----171126modified-------180204modified

	m_hGeometryParameters["MeshHolderOuterRadius"] = GetGeometryParameter("InnerPTFEOuterRadius") + GetGeometryParameter("RibandInnerPTFEHolderThickness");//----------180204modified
	m_hGeometryParameters["MeshHolderInnerRadius"] = GetGeometryParameter("MeshHolderOuterRadius") - GetGeometryParameter("MeshHolderThickness");//----------180204modified

	m_hGeometryParameters["AnodeMeshZshift"] = GetGeometryParameter("AnodeToSurface");//5.5mm
	m_hGeometryParameters["GateMeshZshift"] = 
		GetGeometryParameter("LXeSDHeight") 
		- GetGeometryParameter("GateToSurface");//1190.5-5.5=1185mm
	m_hGeometryParameters["CathodeMeshZshift"] = 0 * mm;
	m_hGeometryParameters["ScreenMeshZshift"] = 0 * mm + GetGeometryParameter("ScreenToBottomPTFE");//5mm

	m_hGeometryParameters["AnodeMeshHolderZshift"] = 
		GetGeometryParameter("AnodeMeshZshift") 
		- GetGeometryParameter("GXeSkinSDHeight") / 2 
		+ GetGeometryParameter("MeshThickness");//-----180119modified
	m_hGeometryParameters["GateMeshHolderZshift"] = GetGeometryParameter("GateMeshZshift") - GetGeometryParameter("LXeSkinSDHeight") / 2 + GetGeometryParameter("LXeHSDHeight") - GetGeometryParameter("MeshHolderHeight");//-----180119modified 
	m_hGeometryParameters["CathodeMeshHolderZshift"] = -GetGeometryParameter("LXeSkinSDHeight") / 2 + GetGeometryParameter("LXeHSDHeight") - GetGeometryParameter("MeshHolderHeight");//-----180123modified
	m_hGeometryParameters["ScreenMeshHolderZshift"] = -GetGeometryParameter("LXeSkinSDHeight") / 2;//-----180123modified

  //================================== copper shaping rings =================================

	m_hGeometryParameters["ShapingRingHeight"] = 8.0 * mm;//-----171126modified
	m_hGeometryParameters["ShapingRingThickness"] = 3.0 * mm;//-----171126modified

	m_hGeometryParameters["ShapingRingInnerRadius"] = GetGeometryParameter("InnerPTFEOuterRadius");
	m_hGeometryParameters["ShapingRingOuterRadius"] = GetGeometryParameter("InnerPTFEOuterRadius") + GetGeometryParameter("ShapingRingThickness");

	m_hGeometryParameters["ShapingRingDz"] = (GetGeometryParameter("LXeSDHeight") - GetGeometryParameter("GateToSurface") - 2 * GetGeometryParameter("MeshHolderHeight")) / (GetGeometryParameter("NbShapingRings") + 1);//61;

	m_hGeometryParameters["FirstShapingRingZshift"] = GetGeometryParameter("GateMeshHolderZshift") - GetGeometryParameter("ShapingRingDz") / 2 - GetGeometryParameter("ShapingRingHeight");

	//=================================== copperinsertion =====================

	m_hGeometryParameters["CopperInsertionInnerRadius"] = GetGeometryParameter("InnerVesselInnerRadius");
	m_hGeometryParameters["CopperInsertionBarrelHeight"] = GetGeometryParameter("InnerVesselBarrelHeight");

	m_hGeometryParameters["CopperInsertionOuterRadius"] = GetGeometryParameter("CopperInsertionInnerRadius") + GetGeometryParameter("CopperInsertionThickness");

	m_hGeometryParameters["CopperInsertionBarrelInnerRadius"] = GetGeometryParameter("CopperInsertionInnerRadius");
	m_hGeometryParameters["CopperInsertionBarrelOuterRadius"] = GetGeometryParameter("CopperInsertionOuterRadius");

	m_hGeometryParameters["CopperInsertionDomeInnerRadius"] = 2 * GetGeometryParameter("CopperInsertionInnerRadius");
	m_hGeometryParameters["CopperInsertionDomeOuterRadius"] = 2 * GetGeometryParameter("CopperInsertionOuterRadius");

	m_hGeometryParameters["CopperInsertionDomeOuterHeight"] = GetGeometryParameter("CopperInsertionDomeOuterRadius") - sqrt(GetGeometryParameter("CopperInsertionDomeOuterRadius") * GetGeometryParameter("CopperInsertionDomeOuterRadius") - GetGeometryParameter("CopperInsertionOuterRadius") * GetGeometryParameter("CopperInsertionOuterRadius"));
	m_hGeometryParameters["CopperInsertionDomeInnerHeight"] = GetGeometryParameter("CopperInsertionDomeInnerRadius") - sqrt(GetGeometryParameter("CopperInsertionDomeInnerRadius") * GetGeometryParameter("CopperInsertionDomeInnerRadius") - GetGeometryParameter("CopperInsertionInnerRadius") * GetGeometryParameter("CopperInsertionInnerRadius"));
	m_hGeometryParameters["CopperInsertionZShift"] = -GetGeometryParameter("OuterVesselCopperInsertionZShift");

	//=================================== cubarrel =====================================

	m_hGeometryParameters["CuBarrelHeight"] = GetGeometryParameter("InnerVesselBarrelHeight");
	m_hGeometryParameters["CuBarrelOuterRadius"] = GetGeometryParameter("InnerVesselInnerRadius");
	m_hGeometryParameters["CuBarrelInnerRadius"] = GetGeometryParameter("CuBarrelOuterRadius") - GetGeometryParameter("CopperInsertionThickness");

	//================================== ribs ===================================

	m_hGeometryParameters["RibThickness"] = 15 * mm;//-----171126modified
	m_hGeometryParameters["RibWidth"] = 25 * mm;//-----171126modified

	m_hGeometryParameters["RibHeight"] = GetGeometryParameter("ShapingRingDz") - GetGeometryParameter("ShapingRingHeight");

	m_hGeometryParameters["NbRibs"] = GetGeometryParameter("NbShapingRings");

	m_hGeometryParameters["FirstRibsZshift"] = GetGeometryParameter("FirstShapingRingZshift") - GetGeometryParameter("ShapingRingDz") / 2 + GetGeometryParameter("ShapingRingHeight") / 2;

	//================================== Hoist Rods ============================

	m_hGeometryParameters["NbHoistRods"] = GetGeometryParameter("NumSides") / 4;//180119modified

	m_hGeometryParameters["HoistRodsRadius"] = 6 * mm;//180119modified
	m_hGeometryParameters["HoistRodsHeight"] = GetGeometryParameter("TopSpace");

	m_hGeometryParameters["HoistRodsDistance"] = 35 * mm;//180119modified

	m_hGeometryParameters["HoistRodsZShift"] = 0 - GetGeometryParameter("GXeHeight") / 2 + GetGeometryParameter("GXeSDHeight") + GetGeometryParameter("PTFEPlateThickness") + GetGeometryParameter("CuPlateThickness") + GetGeometryParameter("HoistRodsHeight") / 2;//180119modified

   //================================== resistor =================================  

	m_hGeometryParameters["EpoxyThickness"] = 0.1 * mm;

	m_hGeometryParameters["NbResistors"] = GetGeometryParameter("NbShapingRings");//-----180119modified

	m_hGeometryParameters["ResistorHeight"] = 0.5 * mm;
	m_hGeometryParameters["ResistorDz"] = GetGeometryParameter("ShapingRingDz");
	m_hGeometryParameters["FirstResistorZshift"] = GetGeometryParameter("FirstRibsZshift");//---------180119modified

  //==============================Side PTFE Holder========================================== 

	m_hGeometryParameters["NbSidePTFEHolder"] = GetGeometryParameter("NumSides");

	m_hGeometryParameters["SidePTFEHeight"] = GetGeometryParameter("InnerVesselBarrelHeight") - GetGeometryParameter("DistanceBottom");
	m_hGeometryParameters["SidePTFEWidth"] = 45. * mm;//-----171126modified
	m_hGeometryParameters["SidePTFEThickness"] = 18 * mm;//-----171126modified

	m_hGeometryParameters["SidePTFEInnerWidth"] = 25 * mm;//-----171126modified
	m_hGeometryParameters["SidePTFEInnerThickness"] = GetGeometryParameter("RibandInnerPTFEHolderThickness") - GetGeometryParameter("RibThickness");//-----171126modified//-----180204modified
	m_hGeometryParameters["SidePTFEInnerHeight"] = GetGeometryParameter("CathodeToGate") - GetGeometryParameter("MeshHolderHeight") * 2 - GetGeometryParameter("PTFEPlateThickness") * 2;//-------180119modified

  //============================================= Over flow chamber  ========================================//

	m_hGeometryParameters["FlowChamberOuterRadius"] = GetGeometryParameter("InnerVesselDomeInnerRadius") / 6;
	m_hGeometryParameters["FlowChamberOuterHeight"] = GetGeometryParameter("InnerVesselDomeInnerHeight") / 2;
	m_hGeometryParameters["FlowChamberThickness"] = 5 * mm;
	m_hGeometryParameters["FlowChamberInnerRadius"] = GetGeometryParameter("FlowChamberOuterRadius") - GetGeometryParameter("FlowChamberThickness");
	m_hGeometryParameters["FlowChamberInnerHeight"] = GetGeometryParameter("FlowChamberOuterHeight") - GetGeometryParameter("FlowChamberThickness") * 2;

	m_hGeometryParameters["FlowChamberZShift"] = 0 - GetGeometryParameter("InnerVesselBarrelHeight") / 2 - GetGeometryParameter("FlowChamberOuterHeight") / 2 - (GetGeometryParameter("InnerVesselDomeInnerHeight") - GetGeometryParameter("FlowChamberOuterHeight")) / 2;

	//========================================== Top PMTs ===========================================

	m_hGeometryParameters["PmtWidth"] = 25.4 * mm;
	m_hGeometryParameters["PmtSpacing"] = 2.15 * mm;
	m_hGeometryParameters["PmtWindowWidth"] = 25.00 * mm;
	m_hGeometryParameters["PmtWindowThickness"] = 1.50 * mm;
	m_hGeometryParameters["PmtCasingWidth"] = 25.40 * mm;
	m_hGeometryParameters["PmtCasingHeight"] = 26.95 * mm;
	m_hGeometryParameters["PmtCasingThickness"] = 0.50 * mm;
	m_hGeometryParameters["PmtBaseThickness"] = 2.00 * mm;

	//==================================== bottom PMTs 3inch R11410 ==================================
	m_hGeometryParameters["R3PmtWindowDiameter"] = 64.0 * mm;
	m_hGeometryParameters["R3PmtWindowThickness"] = 1.5 * mm;
	m_hGeometryParameters["R3PmtCathodeDiameter"] = 64.0 * mm;
	m_hGeometryParameters["R3PmtCathodeThickness"] = 0.5 * mm;
	m_hGeometryParameters["R3PmtCasingnumZPlanes"] = 4;
	m_hGeometryParameters["R3PmtCasingThickness"] = 0.5 * mm;
	m_hGeometryParameters["R3PmtCasingDiameterFirstPlane"] = 53.0 * mm;
	m_hGeometryParameters["R3PmtCasingDiameterSecondPlane"] = 53.0 * mm;
	m_hGeometryParameters["R3PmtCasingDiameterThirdPlane"] = 77.0 * mm;
	m_hGeometryParameters["R3PmtCasingDiameterFourthPlane"] = 77.0 * mm;
	m_hGeometryParameters["R3PmtCasingZFirstPlane"] = 0.0 * mm;
	m_hGeometryParameters["R3PmtCasingZSecondPlane"] = 88.9 * mm;
	m_hGeometryParameters["R3PmtCasingZThirdPlane"] = 108.9 * mm;
	m_hGeometryParameters["R3PmtCasingZFourthPlane"] = 115.9 * mm;
	m_hGeometryParameters["R3PmtCasingHeight"] = 115.9 * mm;
	m_hGeometryParameters["R3PmtBaseDiameter"] = 53.0 * mm;
	m_hGeometryParameters["R3PmtBaseThickness"] = 1.50 * mm;

	//======================================== PandaXLab =========================================//

	m_hGeometryParameters["WaterLength"] = 10 * m;
	m_hGeometryParameters["WaterWidth"] = 10 * m;
	m_hGeometryParameters["WaterHeight"] = 10 * m;

	m_hGeometryParameters["SteelWallThickness"] = 0.3 * m;
	m_hGeometryParameters["ConcreteWallThickness"] = 0.3 * m;
	m_hGeometryParameters["InAirWallThickness"] = 0.3 * m;
	m_hGeometryParameters["MarbleWallThickness"] = 0.3 * m;

	m_hGeometryParameters["MarbleLength"] = 30 * m;
	m_hGeometryParameters["MarbleWidth"] = 30 * m;
	m_hGeometryParameters["MarbleHeight"] = 20 * m;

	m_hGeometryParameters["SteelLength"] = GetGeometryParameter("WaterLength") + GetGeometryParameter("SteelWallThickness");
	m_hGeometryParameters["SteelWidth"] = GetGeometryParameter("WaterWidth") + GetGeometryParameter("SteelWallThickness");
	m_hGeometryParameters["SteelHeight"] = GetGeometryParameter("WaterHeight") + GetGeometryParameter("SteelWallThickness");

	m_hGeometryParameters["ConcreteLength"] = GetGeometryParameter("SteelLength") + GetGeometryParameter("ConcreteWallThickness");
	m_hGeometryParameters["ConcreteWidth"] = GetGeometryParameter("SteelWidth") + GetGeometryParameter("ConcreteWallThickness");
	m_hGeometryParameters["ConcreteHeight"] = GetGeometryParameter("SteelHeight");

	m_hGeometryParameters["InAirLength"] = GetGeometryParameter("ConcreteLength");
	m_hGeometryParameters["InAirWidth"] = GetGeometryParameter("ConcreteWidth") + GetGeometryParameter("InAirWallThickness");
	m_hGeometryParameters["InAirHeight"] = GetGeometryParameter("ConcreteHeight");

	m_hGeometryParameters["AirLength"] = GetGeometryParameter("MarbleLength");
	m_hGeometryParameters["AirWidth"] = GetGeometryParameter("MarbleWidth");
	m_hGeometryParameters["AirHeight"] = GetGeometryParameter("MarbleHeight") * 2;

	//================================== Testing Lab ==================================//

	m_hGeometryParameters["TestModelRadius"] = GetGeometryParameter("OuterVesselOuterRadius") * 2;
	m_hGeometryParameters["TestModelZShift"] = 0 + GetGeometryParameter("TestModelHandZShift") + GetGeometryParameter("OuterVesselHeight") / 2 + GetGeometryParameter("TestModelThickness") / 2 + GetGeometryParameter("OuterVesselOuterDomeHeight") + GetGeometryParameter("DetectorZShift");

	m_hGeometryParameters["TestSideModelWidth"] = GetGeometryParameter("OuterVesselOuterRadius") * 2;
	m_hGeometryParameters["TestSideModelHeight"] = GetGeometryParameter("OuterVesselHeight") - 2 * GetGeometryParameter("OuterVesselFlangeHeight");
	m_hGeometryParameters["TestSideModelXShift"] = GetGeometryParameter("OuterVesselOuterRadius") + GetGeometryParameter("TestSideModelHandXShift") + GetGeometryParameter("TestSideModelThickness") / 2;

	//=========================== PMT for PandaX-II ==================================//

	m_hGeometryParameters["NbTopPMTsII"] = 55;
	m_hGeometryParameters["NbBottomPMTsII"] = 55;
	m_hGeometryParameters["RowsTopPMTII"] = 9;
	m_hGeometryParameters["TopPMTDistanceII"] = 79 * mm;
	m_hGeometryParameters["RowsBottomPMTII"] = 9;
	m_hGeometryParameters["BottomPMTDistanceII"] = 79 * mm;

	m_hGeometryParameters["NbTopVetoPmtsII"] = GetGeometryParameter("NumSides");
	m_hGeometryParameters["NbBottomVetoPmtsII"] = GetGeometryParameter("NumSides");
	m_hGeometryParameters["NbVetoPmtII"] = GetGeometryParameter("NumSides");
	m_hGeometryParameters["RowsVetoPmtII"] = 1;
	m_hGeometryParameters["Nb1RowVetoPmtII"] = GetGeometryParameter("NumSides");

	m_hGeometryParameters["1RowVetoPmtDistanceII"] = 2 * (GetGeometryParameter("CuPlateRadius") - GetGeometryParameter("ShieldSpace") / 2 + 5 * mm) / GetGeometryParameter("NbVetoPmtII");

	//=========================== PMT for PandaX-V ==================================//

	m_hGeometryParameters["NbTopPMTsV"] = 55;
	m_hGeometryParameters["NbBottomPMTsV"] = 55;
	m_hGeometryParameters["RowsTopPMTV"] = 9;
	m_hGeometryParameters["TopPMTDistanceV"] = 79 * mm;
	m_hGeometryParameters["RowsBottomPMTV"] = 9;
	m_hGeometryParameters["BottomPMTDistanceV"] = 79 * mm;

	m_hGeometryParameters["NbTopVetoPmtsV"] = GetGeometryParameter("NumSides");
	m_hGeometryParameters["NbBottomVetoPmtsV"] = GetGeometryParameter("NumSides");
	m_hGeometryParameters["NbVetoPmtV"] = GetGeometryParameter("NumSides");
	m_hGeometryParameters["RowsVetoPmtV"] = 1;
	m_hGeometryParameters["Nb1RowVetoPmtV"] = GetGeometryParameter("NumSides");

	m_hGeometryParameters["1RowVetoPmtDistanceV"] = 2 * (GetGeometryParameter("CuPlateRadius") - GetGeometryParameter("ShieldSpace") / 2 + 5 * mm) / GetGeometryParameter("NbVetoPmtV");


	//=========================== PMT for PandaX-IIII ==================================//

	m_hGeometryParameters["NbBottomPMTsIIII"] = 199;
	m_hGeometryParameters["NbTopPMTsIIII"] = 169;

	m_hGeometryParameters["RowsTopPMTIIII"] = 9;
	m_hGeometryParameters["TopPMTDistanceIIII"] = 79 * mm;
	m_hGeometryParameters["RowsBottomPMTIIII"] = 9;
	m_hGeometryParameters["BottomPMTDistanceIIII"] = 79 * mm;

	m_hGeometryParameters["NbTopVetoPmtsIIII"] = GetGeometryParameter("NumSides") * 3;//-------180119modified
	m_hGeometryParameters["NbBottomVetoPmtsIIII"] = GetGeometryParameter("NumSides") * 3;//-------180119modified
	m_hGeometryParameters["NbVetoPmtIIII"] = GetGeometryParameter("NumSides") * 3;//-------180119modified
	m_hGeometryParameters["RowsVetoPmtIIII"] = 1;
	m_hGeometryParameters["Nb1RowVetoPmtIIII"] = GetGeometryParameter("NumSides") * 3;//-------180119modified

	m_hGeometryParameters["1RowVetoPmtDistanceIIII"] = 2 * (630. * mm + GetGeometryParameter("PmtCasingWidth") / 2.) / GetGeometryParameter("NbVetoPmtIIII");
}



