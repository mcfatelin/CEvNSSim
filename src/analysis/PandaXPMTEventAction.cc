#include "analysis/PandaXPMTEventAction.hh"
#include "analysis/PandaXPMTDM.hh"

#include "BambooGlobalVariables.hh"

#include <G4Event.hh>

PandaXPMTEventAction::PandaXPMTEventAction(shared_ptr<PandaXPMTDM> manager)
    : _dataManager{manager} {
    _dataManager->_eventId = 0;
}

PandaXPMTEventAction::~PandaXPMTEventAction() {
    G4cout << "PandaXPMTEventAction destructed." << G4endl;
}

void PandaXPMTEventAction::BeginOfEventAction(const G4Event *aEvent) {
    int eventId = aEvent->GetEventID();
    _dataManager->_eventId = eventId;
    _dataManager->_partialSaved = false;
    if (eventId % 100000 == 0) {
        G4cout << "Processing event " << eventId << "..." << G4endl;
    }
}

void PandaXPMTEventAction::EndOfEventAction(const G4Event *aEvent) {
    _dataManager->fillEvent(aEvent);
}
