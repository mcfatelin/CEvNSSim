#include "analysis/PandaXPMTStackingAction.hh"
#include "analysis/PandaXPMTSteppingAction.hh"

#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"

PandaXPMTStackingAction::PandaXPMTStackingAction(shared_ptr<PandaXPMTDM> dm)
    : _manager{dm} {}

PandaXPMTStackingAction::~PandaXPMTStackingAction() {}

G4ClassificationOfNewTrack
PandaXPMTStackingAction::ClassifyNewTrack(const G4Track * aTrack){
 
  //Count what process generated the optical photons
  if(aTrack->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition()){
    // particle is optical photon
    if(aTrack->GetParentID()>0){/*
      // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName()=="Scintillation")
        eventInformation->IncPhotonCount_Scint();
      else if(aTrack->GetCreatorProcess()->GetProcessName()=="Cerenkov")
      eventInformation->IncPhotonCount_Ceren();
				*/}
  }
  else{
  }
  return fUrgent;
}

void PandaXPMTStackingAction::NewStage() {
    // all the urgent tracks have been processed. So we can save the results.
    _manager->fillEvent(
        G4EventManager::GetEventManager()->GetConstCurrentEvent(), true);
}

void PandaXPMTStackingAction::PrepareNewEvent() {}
