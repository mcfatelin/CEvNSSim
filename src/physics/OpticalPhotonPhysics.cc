#include "physics/OpticalPhotonPhysics.hh"
#include "BambooGlobalVariables.hh"
#include "physics/BambooPhysicsFactory.hh"

#include <G4DataQuestionaire.hh>
#include <G4EmLivermorePhysics.hh>

#include <G4DecayPhysics.hh>
#include <G4OpticalPhysics.hh>
#include <G4StoppingPhysics.hh>

#include <G4HadronElasticPhysicsHP.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4HadronPhysicsShielding.hh>
#include <G4EmExtraPhysics.hh>
#include <G4IonQMDPhysics.hh>

//#include <G4OpticalProcessIndex.hh> !!!

//#include <G4ComptonScattering.hh>
//#include <G4eMultipleScattering.hh>
//#include <G4eplusAnnihilation.hh>
//#include <G4eIonisation.hh>
//#include <G4PhotoElectricEffect.hh>
//#include <G4eBremsstrahlung.hh>
//#include <G4GammaConversion.hh>

#include <QString>

PhysicsRegister<OpticalPhotonPhysics> OpticalPhotonPhysics::reg("OpticalPhotonPhysics");

OpticalPhotonPhysics::OpticalPhotonPhysics(const G4String &name)
    : BambooPhysics(name) {

    G4DataQuestionaire it(photon,neutron,optical,radioactive);

    G4cout << "Physics List: " << _name << G4endl;

    std::string dcV =
        BambooGlobalVariables::Instance()->getPhysicsParameterAsString("cutlength");

    if (dcV.empty()) 
        defaultCutValue = 0.001 * mm;
    else 
    {
        std::string::size_type n = dcV.find("*");
        double unit;
        if (n != std::string::npos) 
        {
            unit = BambooGlobalVariables::Instance()->getUnitByName(dcV.substr(n + 1));
            defaultCutValue = QString(dcV.substr(0, n).c_str()).toDouble() * unit;
        } 
        else 
            defaultCutValue = QString(dcV.c_str()).toDouble() * mm;
    }

    G4cout << "default cut length: " << defaultCutValue / mm << " mm" << G4endl;

    G4int verbose = 1;

	

    // EM Physics
	// LXeEMPhysics
    RegisterPhysics(new G4EmLivermorePhysics(verbose));

    // Synchroton Radiation & GN Physics
    RegisterPhysics(new G4EmExtraPhysics(verbose));

    // Decays
    // LXeGeneralPhysics
    RegisterPhysics(new G4DecayPhysics(verbose));

	
	// OpticalPhysics
	RegisterPhysics(new G4OpticalPhysics(verbose));
	//RegisterPhysics(new G4OpticalProcessIndex(verbose));
	
    RegisterPhysics(new G4RadioactiveDecayPhysics(verbose));

    // hadron physics
    RegisterPhysics(new G4HadronElasticPhysicsHP(verbose));

// shielding, changed api for different version of geant4.
#ifdef G4VERSION_NUMBER
#if G4VERSION_NUMBER < 1000
    RegisterPhysics(new HadronPhysicsShielding(verbose));
#else
    RegisterPhysics(new G4HadronPhysicsShielding(verbose));
#endif
#endif
    // stopping physics
    // G4MuonMinusCapture
    RegisterPhysics(new G4StoppingPhysics(verbose));

    // ion physics
    RegisterPhysics(new G4IonQMDPhysics(verbose));
}

OpticalPhotonPhysics::~OpticalPhotonPhysics()
{
    G4cout << "OpticalPhotonPhysics destructed." << G4endl;
}
