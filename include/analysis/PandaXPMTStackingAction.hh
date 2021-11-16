#ifndef PandaXPMTStackingAction_H
#define PandaXPMTStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "analysis/PandaXPMTDM.hh"

#include <memory>

class PandaXPMTStackingAction : public G4UserStackingAction
{
  public:

    PandaXPMTStackingAction(shared_ptr<PandaXPMTDM> dm);
    virtual ~PandaXPMTStackingAction();
 
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();
    void setDataManager(PandaXPMTDM *manager);
 
  private:
    shared_ptr<PandaXPMTDM> _manager;
};

#endif
