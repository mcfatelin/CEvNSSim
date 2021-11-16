#ifndef PandaXPMTTrackingAction_h
#define PandaXPMTTrackingAction_h 1

#include "analysis/PandaXPMTDM.hh"
#include "G4UserTrackingAction.hh"
#include "globals.hh"

using std::shared_ptr;

class G4Track;

class PandaXPMTTrackingAction : public G4UserTrackingAction {

  public:

    PandaXPMTTrackingAction(shared_ptr<PandaXPMTDM> dm);
    ~PandaXPMTTrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

  void setDataManager(PandaXPMTDM *manager);

  private:
    shared_ptr<PandaXPMTDM> _manager;
};

#endif
