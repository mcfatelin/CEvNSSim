#ifndef PANDAXPMTEVENTACTION_H
#define PANDAXPMTEVENTACTION_H

#include <G4UserEventAction.hh>

#include <memory>

using std::shared_ptr;

class G4Event;
class PandaXPMTDM;

class PandaXPMTEventAction : public G4UserEventAction {
public:
    PandaXPMTEventAction(shared_ptr<PandaXPMTDM> manager);

    virtual ~PandaXPMTEventAction();

    virtual void BeginOfEventAction(const G4Event *aEvent);

    virtual void EndOfEventAction(const G4Event *aEvent);

    void setUserSeed(long seed);

private:
    shared_ptr<PandaXPMTDM> _dataManager;
    long user_seed = -1;
};

inline void PandaXPMTEventAction::setUserSeed(long seed)
{
    user_seed = seed;
}
#endif // PANDAXPMTEVENTACTION_H
