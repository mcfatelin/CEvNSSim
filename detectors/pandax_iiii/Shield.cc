#include "Shield.hh"
#include "detector/BambooDetectorFactory.hh"
#include "BambooGlobalVariables.hh"


DetectorRegister<Shield> Shield::reg("Shield");

/*namespace {

  BambooDetectorPart * createShield ()
  {
    return new Shield("Shield");
  }

  const std::string ShieldName("Shield");

  const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(ShieldName, createShield);
}
*/

Shield::Shield (const G4String & name)
  : BambooDetectorPart(name)
{
  //BambooGlobalVariables *bgv = BambooGlobalVariables::Instance();
  G4cout << "Shield found..." << G4endl;
}

G4bool Shield::construct()
{


  return true;
}



