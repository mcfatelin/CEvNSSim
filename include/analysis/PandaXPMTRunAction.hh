#ifndef PandaXPMTRunAction_H
#define PandaXPMTRunAction_H

#include <G4UserRunAction.hh>
#include <analysis/PandaXPMTDM.hh>

#include <memory>

using std::shared_ptr;

class G4Run;
class PandaXPMTDM;

class PandaXPMTRunAction : public G4UserRunAction {
public:
    PandaXPMTRunAction(shared_ptr<PandaXPMTDM> manager);

    virtual ~PandaXPMTRunAction();

    virtual void BeginOfRunAction(const G4Run *aRun);

    virtual void EndOfRunAction(const G4Run *aRun);

private:
    shared_ptr<PandaXPMTDM> _dataManager;
};

#endif // PandaXPMTRunAction_H
