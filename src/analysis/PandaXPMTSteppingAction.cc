#include "analysis/PandaXPMTSteppingAction.hh"
#include "analysis/PandaXPMTEventAction.hh"
#include "analysis/PandaXPMTTrackingAction.hh"
#include "analysis/PandaXPMTSD.hh"

#include <G4SteppingManager.hh>
#include <G4SDManager.hh>
#include <G4EventManager.hh>
#include <G4ProcessManager.hh>
#include <G4Track.hh>
#include <G4Step.hh>
#include <G4Event.hh>
#include <G4StepPoint.hh>
#include <G4TrackStatus.hh>
#include <G4VPhysicalVolume.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTypes.hh>

PandaXPMTSteppingAction::PandaXPMTSteppingAction(shared_ptr<PandaXPMTDM> dm)
    : _manager{dm} {}

PandaXPMTSteppingAction::~PandaXPMTSteppingAction() {}

void PandaXPMTSteppingAction::UserSteppingAction(const G4Step * theStep){

  G4Track* theTrack = theStep->GetTrack();
  
  //G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
  //G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();

  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  //G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();
  
  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  static G4ThreadLocal G4OpBoundaryProcess* boundary=NULL;

  //find the boundary process only once
  if(!boundary){
    G4ProcessManager* pm
      = theStep->GetTrack()->GetDefinition()->GetProcessManager();
    int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    int i;
    for( i=0;i<nprocesses;i++){
      if((*pv)[i]->GetProcessName()=="OpBoundary"){
        boundary = (G4OpBoundaryProcess*)(*pv)[i];
        break;
      }
    }
  }

  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
    if(theTrack->GetTrackStatus()==fStopAndKill){
      if(theTrack->GetTouchableHandle()->GetVolume()==0)_manager->lastTouchableVolume.push_back("outOfWorld");
      else
        _manager->lastTouchableVolume.push_back(theTrack->GetTouchableHandle()->GetVolume()->GetName());
      //_manager->photDeathPlace.push_back(theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName());
      if(theStep->GetPostStepPoint()->GetProcessDefinedStep())_manager->killerProcess.push_back(theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());else _manager->killerProcess.push_back("NOkillerProcess");
      if(theStep->GetPreStepPoint()->GetProcessDefinedStep())_manager->prekillerProcess.push_back(theStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName());else _manager->prekillerProcess.push_back("NOprekillerProcess");
      if(theStep->GetPreStepPoint()->GetPhysicalVolume())_manager->lastStepPreVol.push_back(theStep->GetPreStepPoint()->GetPhysicalVolume()->GetName());else _manager->lastStepPreVol.push_back("NOlastStepPreVol");
      if(theStep->GetPostStepPoint()->GetPhysicalVolume())_manager->lastStepPostVol.push_back(theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName());else _manager->lastStepPostVol.push_back("NOlastStepPostVol");
      //G4cout<<theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()<<" killed a photon\n";
      _manager->lastStepLength.push_back(theStep->GetStepLength());
      _manager->lastStepEdep.push_back(theStep->GetTotalEnergyDeposit());
    }

    boundaryStatus=boundary->GetStatus();
    _manager->opBoundStatus.push_back(int(boundaryStatus));

    //Check to see if the partcile was actually at a boundary
    //Otherwise the boundary status may not be valid
    //Prior to Geant4.6.0-p1 this would not have been enough to check
    if(thePostPoint->GetStepStatus()==fGeomBoundary && boundaryStatus==Detection){
        //Note, this assumes that the volume causing detection
        //is the photocathode because it is the only one with
        //non-zero efficiency
        //Triger sensitive detector manually since photon is
        //absorbed but status was Detection
        G4SDManager* SDman = G4SDManager::GetSDMpointer();
        G4String sdName="VolPmtSD";
        PandaXPMTSD* pmtSD = (PandaXPMTSD*)SDman->FindSensitiveDetector(sdName);
        if(pmtSD)pmtSD->ProcessHits_constStep(theStep,NULL);
    }
  }
}
