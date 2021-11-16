#include "analysis/PandaXPMTRunAction.hh"
#include "BambooGlobalVariables.hh"

#include <G4Run.hh>

#include <CLHEP/Random/Randomize.h>

#include <sys/time.h>

PandaXPMTRunAction::PandaXPMTRunAction(shared_ptr<PandaXPMTDM> manager)
    : _dataManager{manager} {}

PandaXPMTRunAction::~PandaXPMTRunAction() {
    G4cout << "PandaXPMTRunAction destructed." << G4endl;
}

void PandaXPMTRunAction::BeginOfRunAction(const G4Run *aRun) {
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    const string &name = BambooGlobalVariables::Instance()->getOutDataName();
    _dataManager->book(name);
    _dataManager->_runId = aRun->GetRunID();
    struct timeval hTimeValue;
    gettimeofday(&hTimeValue, NULL);
    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
    CLHEP::HepRandom::setTheSeed(hTimeValue.tv_usec);
}

void PandaXPMTRunAction::EndOfRunAction(const G4Run *aRun) {
    G4cout << "\n----------End of Run " << aRun->GetRunID() << "----------\n";
    _dataManager->save();
}
