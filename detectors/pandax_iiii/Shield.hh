#ifndef SHIELD_H
#define SHIELD_H

#include "detector/BambooDetectorPart.hh"
#include "detector/BambooDetectorFactory.hh"


class Shield : public BambooDetectorPart
{

public:

  Shield(const G4String &name);

  virtual G4bool construct();

	static DetectorRegister<Shield> reg;
private:


};


#endif // SHIELD_H

