#include "analysis/PandaXPMTAnalysis.hh"
#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"
#include "analysis/BambooAnalysisFactory.hh"
#include "analysis/PandaXPMTEventAction.hh"
#include "analysis/PandaXPMTRunAction.hh"
#include "analysis/PandaXPMTStackingAction.hh"
#include "analysis/PandaXPMTSteppingAction.hh"
#include "analysis/PandaXPMTTrackingAction.hh"

AnalysisRegister<PandaXPMTAnalysis> PandaXPMTAnalysis::reg("PandaXPMTAnalysis");

PandaXPMTAnalysis::PandaXPMTAnalysis(const G4String &name)
    : BambooAnalysis(name), dm{nullptr}
{
    int dPMT =
        BambooGlobalVariables::Instance()->getAnalysisParameterAsInt(
            "EnablePMT");
    int dNullEvent =
        BambooGlobalVariables::Instance()->getAnalysisParameterAsInt(
            "save_null_event");
    std::string user_seed_string =
        BambooGlobalVariables::Instance()->getAnalysisParameterAsString(
            "user_seed");
    bool enablePMT(true);
    if (dPMT == 0) {
        enablePMT = false;
    }
    if (dPMT != 0 && dPMT != 1) {
        G4cout << "EnablePMT can only be 0(false) or 1(true). 1 "
                  "will be used in the simulation."
               << G4endl;
    }
    
    long user_seed = -1;
    if (user_seed_string.size() != 0) {
        G4cout << "User seed provided " << user_seed_string << G4endl;
        user_seed = stol(user_seed_string);
    }

    dm = shared_ptr<PandaXPMTDM> {new PandaXPMTDM(enablePMT)};
    if (dNullEvent == 1) {
        dm->saveNullEvent(true);
    }
    _runAction = new PandaXPMTRunAction(dm);
    _eventAction = new PandaXPMTEventAction(dm);
    if (user_seed != -1) {
        dynamic_cast<PandaXPMTEventAction*>(_eventAction)->setUserSeed(user_seed);
    }
    _trackingAction = new PandaXPMTTrackingAction(dm);
    _steppingAction = new PandaXPMTSteppingAction(dm);
}

PandaXPMTAnalysis::~PandaXPMTAnalysis()
{
    G4cout << "Destructing PandaXPMTAnalysis..." << G4endl;
}
