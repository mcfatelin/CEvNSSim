#ifndef OPTICALPHOTONPHYSICS_H
#define OPTICALPHOTONPHYSICS_H

#include "physics/BambooPhysics.hh"
#include "physics/BambooPhysicsFactory.hh"

class OpticalPhotonPhysics : public BambooPhysics {
public:
    OpticalPhotonPhysics(const G4String &name);

    ~OpticalPhotonPhysics();

    static PhysicsRegister<OpticalPhotonPhysics> reg;
};
#endif // OPTICALPHOTONPHYSICS_H
