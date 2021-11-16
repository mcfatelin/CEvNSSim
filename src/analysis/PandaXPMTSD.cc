#include "analysis/PandaXPMTSD.hh"
#include "analysis/PandaXPMTHit.hh"

#include <G4VPhysicalVolume.hh>
#include <G4LogicalVolume.hh>
#include <G4Track.hh>
#include <G4Step.hh>
#include <G4VTouchable.hh>
#include <G4TouchableHistory.hh>
#include <G4ios.hh>
#include <G4ParticleTypes.hh>
#include <G4ParticleDefinition.hh>

//#define DEBUG_PMT_POSITIONS
//#define DEBUG_PMT_HITS
//#define DEBUG_HIT_STEP

PandaXPMTSD::PandaXPMTSD(G4String name)
  : G4VSensitiveDetector(name),fPMTHitCollection(0)
  , fPMTPositionsX(new G4DataVector())
  , fPMTPositionsY(new G4DataVector())
  , fPMTPositionsZ(new G4DataVector())
{
  collectionName.insert("pmtHitCollection");
}

PandaXPMTSD::~PandaXPMTSD() {}

void PandaXPMTSD::SetPmtPositions(const std::vector<G4ThreeVector>& positions)
{
  for (int i=0; i<int(positions.size()); ++i) {
    #ifdef DEBUG_PMT_POSITIONS 
    G4cout << "*** DEBUG *** SET PMT POSITION FOR: " << i << " ("; 
    #endif
    if(fPMTPositionsX){
		fPMTPositionsX->push_back(positions[i].x());
		#ifdef DEBUG_PMT_POSITIONS 
		G4cout << positions[i].x();
		#endif
	} 
	#ifdef DEBUG_PMT_POSITIONS
	G4cout << ",";
	#endif
    if(fPMTPositionsY){
		fPMTPositionsY->push_back(positions[i].y());
		#ifdef DEBUG_PMT_POSITIONS 
		G4cout << positions[i].y();
		#endif
	} 
	#ifdef DEBUG_PMT_POSITIONS 
	G4cout << ",";		
	#endif
    if(fPMTPositionsZ){
		fPMTPositionsZ->push_back(positions[i].z());
		#ifdef DEBUG_PMT_POSITIONS 
		G4cout << positions[i].z();
		#endif
	} 
	#ifdef DEBUG_PMT_POSITIONS 
	G4cout << ")" << G4endl;
	#endif
  }
}

void PandaXPMTSD::Initialize(G4HCofThisEvent* hitsCE){
  fPMTHitCollection = new PandaXPMTHitsCollection
                      (SensitiveDetectorName,collectionName[0]);
  //Store collection with event and keep ID
  static int hitCID = -1;
  if(hitCID<0){
    hitCID = GetCollectionID(0);
  }
  hitsCE->AddHitsCollection( hitCID, fPMTHitCollection );
}

bool PandaXPMTSD::ProcessHits(G4Step* ,G4TouchableHistory* ){
  return false;
}

//Generates a hit and uses the postStepPoint's mother volume replica number
//PostStepPoint because the hit is generated manually when the photon is
//absorbed by the photocathode

bool PandaXPMTSD::ProcessHits_constStep(const G4Step* aStep,
                                       G4TouchableHistory* ){

	#ifdef DEBUG_PMT_HITS
    G4cout << "*** DEBUG *** aStep: " << aStep << G4endl;
    G4cout << "*** DEBUG *** aStep->GetTrack()->GetDefinition()->GetParticleName(): " 
		<< aStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetTrack()->GetDefinition()->GetParticleType(): " 
		<< aStep->GetTrack()->GetDefinition()->GetParticleType() << G4endl;
    #endif

  //need to know if this is an optical photon
  if(aStep->GetTrack()->GetDefinition()
     != G4OpticalPhoton::OpticalPhotonDefinition()) return false;

	// DEBUGGER OF POST STEP POINT: PHYSICAL VOLUME
	#ifdef DEBUG_PMT_HITS
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint(): " << aStep->GetPostStepPoint() << G4endl;

    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetPhysicalVolume(): " 
		<< aStep->GetPostStepPoint()->GetPhysicalVolume() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName(): " 
		<< aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetPhysicalVolume()->GetCopyNo(): " 
		<< aStep->GetPostStepPoint()->GetPhysicalVolume()->GetCopyNo() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetPhysicalVolume(): GetMultiplicity(): " 
		<< aStep->GetPostStepPoint()->GetPhysicalVolume()->GetMultiplicity() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetPhysicalVolume()->IsMany(): " 
		<< aStep->GetPostStepPoint()->GetPhysicalVolume()->IsMany() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetPhysicalVolume()->IsReplicated(): " 
		<< aStep->GetPostStepPoint()->GetPhysicalVolume()->IsReplicated() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName(): " 
		<< aStep->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetPhysicalVolume()->GetMotherLogical()->GetName(): " 
		<< aStep->GetPostStepPoint()->GetPhysicalVolume()->GetMotherLogical()->GetName() << G4endl;

    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetSensitiveDetector(): " 
		<< aStep->GetPostStepPoint()->GetSensitiveDetector() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetSensitiveDetector()->GetName(): " 
		<< aStep->GetPostStepPoint()->GetSensitiveDetector()->GetName() << G4endl;

    #endif  

	// DEBUGGER OF POST STEP POINT: TOUCHABLE
	#ifdef DEBUG_PMT_HITS
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable(): " 
		<< aStep->GetPostStepPoint()->GetTouchable() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0): " 
		<< aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0) << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->GetName(): " 
		<< aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->GetName() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->GetCopyNo(): " 
		<< aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->GetCopyNo() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->GetMultiplicity(): " 
		<< aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->GetMultiplicity() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->IsMany(): " 
		<< aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->IsMany() << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->IsReplicated(): " 
		<< aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0)->IsReplicated() << G4endl;
		
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable()->GetVolume(1): " 
		<< aStep->GetPostStepPoint()->GetTouchable()->GetVolume(1) << G4endl;
    G4cout << "*** DEBUG *** aStep->GetPostStepPoint()->GetTouchable()->GetVolume(1)->GetName(): " 
		<< aStep->GetPostStepPoint()->GetTouchable()->GetVolume(1)->GetName() << G4endl;
		
	#endif

	// DEBUGGER OF STEP AND TRACK INFORMATION
	#ifdef DEBUG_HIT_STEP
	{
		auto aTrack = aStep->GetTrack();
		G4cout << "*** DEBUG: Track: LocalTime: " << aTrack->GetLocalTime() << G4endl;
		G4cout << "*** DEBUG: Track: GlobalTime: " << aTrack->GetGlobalTime() << G4endl;
		G4cout << "*** DEBUG: Track: ProperTime: " << aTrack->GetProperTime() << G4endl;
		
		auto aPreStepPoint = aStep->GetPreStepPoint();
		G4cout << "*** DEBUG: PreStepPoint: LocalTime: " << aPreStepPoint->GetLocalTime() << G4endl;
		G4cout << "*** DEBUG: PreStepPoint: GlobalTime: " << aPreStepPoint->GetGlobalTime() << G4endl;
		G4cout << "*** DEBUG: PreStepPoint: ProperTime: " << aPreStepPoint->GetProperTime() << G4endl;
		
		auto aPostStepPoint = aStep->GetPostStepPoint();
		G4cout << "*** DEBUG: PostStepPoint: LocalTime: " << aPostStepPoint->GetLocalTime() << G4endl;
		G4cout << "*** DEBUG: PostStepPoint: GlobalTime: " << aPostStepPoint->GetGlobalTime() << G4endl;
		G4cout << "*** DEBUG: PostStepPoint: ProperTime: " << aPostStepPoint->GetProperTime() << G4endl;
	}
	#endif

  // User replica number 1 since photocathode is a daughter volume
  // to the pmt which was replicated
  // int pmtNumber = aStep->GetPostStepPoint()->GetTouchable()->GetReplicaNumber(1);
  // G4VPhysicalVolume* physVol = aStep->GetPostStepPoint()->GetTouchable()->GetVolume(1);
  // -------------------------------------------------------------------
  // The information could be retrived from either ways:
  // + aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0), or
  // + aStep->GetPostStepPoint()->GetPhysicalVolume()
  // modified by: PICK (Parinya Namwongsa)
  // -------------------------------------------------------------------
  int pmtNumber= aStep->GetPostStepPoint()->GetTouchable()->GetReplicaNumber(0);
  G4VPhysicalVolume* physVol= aStep->GetPostStepPoint()->GetTouchable()->GetVolume(0);

  //Find the correct hit collection
  //int n=fPMTHitCollection->entries();
  //PandaXPMTHit* hit=NULL;
  //for(int i=0;i<n;i++){
    //if((*fPMTHitCollection)[i]->GetPMTNumber()==pmtNumber){
      //hit=(*fPMTHitCollection)[i];
      //break;
    //}
  //}
 
  //if(hit==NULL){//this pmt wasnt previously hit in this event
    auto hit = new PandaXPMTHit(); //so create new hit
    hit->SetPMTNumber(pmtNumber);
    hit->SetPMTPhysVol(physVol);
    fPMTHitCollection->insert(hit);
    hit->SetPMTPos((*fPMTPositionsX)[pmtNumber],
				   (*fPMTPositionsY)[pmtNumber],
                   (*fPMTPositionsZ)[pmtNumber]);
    hit->SetTimes(aStep->GetTrack()->GetGlobalTime(), 
				  aStep->GetTrack()->GetLocalTime(), 
				  aStep->GetTrack()->GetProperTime());
	hit->SetTrackID(aStep->GetTrack()->GetTrackID());
  //}

  hit->IncPhotonCount(); //increment hit for the selected pmt

  return true;
}

void PandaXPMTSD::EndOfEvent(G4HCofThisEvent* ) {}
