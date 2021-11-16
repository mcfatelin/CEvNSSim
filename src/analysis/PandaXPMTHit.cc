#include "analysis/PandaXPMTHit.hh"
#include <G4ios.hh>
#include <G4VVisManager.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>

G4ThreadLocal G4Allocator<PandaXPMTHit>* PandaXPMTHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PandaXPMTHit::PandaXPMTHit()
  : fPmtNumber(-1),fPhotons(0),fPhysVol(0),fDrawit(false),fPos(), fTimes() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PandaXPMTHit::~PandaXPMTHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PandaXPMTHit::PandaXPMTHit(const PandaXPMTHit &right) : G4VHit()
{
  fPmtNumber=right.fPmtNumber;
  fPhotons=right.fPhotons;
  fPhysVol=right.fPhysVol;
  fDrawit=right.fDrawit;
  fPos=right.fPos;	//Pick
  fTimes=right.fTimes; //Pick
  fTrackID=right.fTrackID; //Pick
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const PandaXPMTHit& PandaXPMTHit::operator=(const PandaXPMTHit &right){
  fPmtNumber = right.fPmtNumber;
  fPhotons=right.fPhotons;
  fPhysVol=right.fPhysVol;
  fDrawit=right.fDrawit;
  fPos=right.fPos;	//Pick
  fTimes=right.fTimes; //Pick
  fTrackID=right.fTrackID; //Pick
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int PandaXPMTHit::operator==(const PandaXPMTHit &right) const{
  return (fPmtNumber==right.fPmtNumber);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PandaXPMTHit::Draw(){
  if(fDrawit&&fPhysVol){ //ReDraw only the PMTs that have hit counts > 0
    //Also need a physical volume to be able to draw anything
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if(pVVisManager){//Make sure that the VisManager exists
      G4VisAttributes attribs(G4Colour(1.,0.,0.));
      attribs.SetForceSolid(true);
      G4RotationMatrix rot;
      if(fPhysVol->GetRotation())//If a rotation is defined use it
        rot=*(fPhysVol->GetRotation());
      G4Transform3D trans(rot,fPhysVol->GetTranslation());//Create transform
      pVVisManager->Draw(*fPhysVol,attribs,trans);//Draw it
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PandaXPMTHit::Print() {}
