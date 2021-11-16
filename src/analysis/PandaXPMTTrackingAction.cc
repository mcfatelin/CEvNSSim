#include "analysis/PandaXPMTTrackingAction.hh"

#include <G4Track.hh>

PandaXPMTTrackingAction::PandaXPMTTrackingAction(shared_ptr<PandaXPMTDM> dm)
    : _manager{dm} {}

PandaXPMTTrackingAction::~PandaXPMTTrackingAction() {}

void PandaXPMTTrackingAction::PreUserTrackingAction(const G4Track *aTrack) {
    std::map<int, std::string> &trackMap = _manager->getTrackMap();
    int trackId = aTrack->GetTrackID();
    if (trackMap.find(trackId) == trackMap.end()) {
        trackMap[trackId] = aTrack->GetParticleDefinition()->GetParticleName();
    }
}

void PandaXPMTTrackingAction::PostUserTrackingAction(const G4Track *) {}
