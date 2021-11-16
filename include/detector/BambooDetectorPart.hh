#ifndef BAMBOODETECTORPART_H
#define BAMBOODETECTORPART_H

#include <G4PhysicalConstants.hh>
#include <G4SystemOfUnits.hh>
#include <globals.hh>
#include <map>
using std::map;

class G4LogicalVolume;
class G4VPhysicalVolume;

class BambooDetectorPart {
  public:
    BambooDetectorPart(const G4String &partName);

    virtual ~BambooDetectorPart() {}

    virtual G4bool construct() = 0;

    G4String getName() const { return partName_; }

    void setParent(BambooDetectorPart *parent);

    G4LogicalVolume *getLogicalVolume();

    G4LogicalVolume *getContainerLogicalVolume();

    G4VPhysicalVolume *getPhysicalVolume();

	void DefineGeometryParameters(const G4String value="MiniPandaX"); // #Pick

  protected:
    G4String partName_;

    G4LogicalVolume *partLogicalVolume_;

    G4LogicalVolume *partContainerLogicalVolume_;

    G4VPhysicalVolume *partPhysicalVolume_;

    BambooDetectorPart *parentPart_;
    
    //void DefineGeometryParametersPandaX2(const G4String value);
    void DefineGeometryParametersPandaX4(const G4String value);
    void DefineGeometryParametersPandaXSP(const G4String value);

  // imported from the previous version of the base class #Pick
  map<G4String, G4double> m_hGeometryParameters;

  G4double GetGeometryParameter(const char *szParameter)
  {
    return m_hGeometryParameters[szParameter];
  }
    
};
#endif
