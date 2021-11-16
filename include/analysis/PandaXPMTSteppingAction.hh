#ifndef PandaXPMTSteppingAction_H
#define PandaXPMTSteppingAction_H 1

#include "analysis/PandaXPMTDM.hh"

#include <globals.hh>
#include <G4UserSteppingAction.hh>

#include <G4OpBoundaryProcess.hh>

using std::shared_ptr;

class G4Step;
class PandaXPMTEventAction;
class PandaXPMTTrackingAction;

class PandaXPMTSteppingAction : public G4UserSteppingAction
{
  public:

  //PandaXPMTSteppingAction(PandaXPMTRecorderBase*);
    PandaXPMTSteppingAction(shared_ptr<PandaXPMTDM> dm);
    virtual ~PandaXPMTSteppingAction();
    virtual void UserSteppingAction(const G4Step*);

  // void SetOneStepPrimaries(bool b){fOneStepPrimaries=b;}
  //bool GetOneStepPrimaries(){return fOneStepPrimaries;}

  void setDataManager(PandaXPMTDM *manager);
 
  private:

  //PandaXPMTRecorderBase* fRecorder;
    shared_ptr<PandaXPMTDM> _manager;
  // bool fOneStepPrimaries;

  // G4OpBoundaryProcessStatus fExpectedNextStatus;
};

#endif
