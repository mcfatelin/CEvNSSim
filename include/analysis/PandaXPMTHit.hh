#ifndef PandaXPMTHit_h
#define PandaXPMTHit_h 1

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>
#include <G4ThreeVector.hh>
#include <G4LogicalVolume.hh>
#include <G4Transform3D.hh>
#include <G4RotationMatrix.hh>
#include <G4VPhysicalVolume.hh>

#include <tls.hh>

class G4VTouchable;

class PandaXPMTHit : public G4VHit
{
  public:
 
    PandaXPMTHit();
    virtual ~PandaXPMTHit();
    PandaXPMTHit(const PandaXPMTHit &right);

    const PandaXPMTHit& operator=(const PandaXPMTHit &right);
    int operator==(const PandaXPMTHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
 
    virtual void Draw();
    virtual void Print();

    inline void SetDrawit(bool b){fDrawit=b;}
    inline G4bool GetDrawit(){return fDrawit;}

    inline void IncPhotonCount(){fPhotons++;}
    inline int GetPhotonCount(){return fPhotons;}

    inline void SetPMTNumber(int n) { fPmtNumber = n; }
    inline int GetPMTNumber() { return fPmtNumber; }

    inline void SetPMTPhysVol(G4VPhysicalVolume* physVol){this->fPhysVol=physVol;}
    inline G4VPhysicalVolume* GetPMTPhysVol(){return fPhysVol;}

    inline void SetPMTPos(double x,double y,double z){
      fPos=G4ThreeVector(x,y,z);
    }
 
    inline G4ThreeVector GetPMTPos(){return fPos;}
    
    inline void SetTimes(G4double global, G4double local, G4double proper=0.)
    { fTimes=G4ThreeVector(global, local, proper); }
    inline G4ThreeVector GetTimes() { return fTimes; }
    
    inline void SetTrackID(int tid) { fTrackID = tid; }
    inline int GetTrackID() { return fTrackID; }

  private:

    int fPmtNumber;
    int fPhotons;
    G4ThreeVector fPos;
    G4VPhysicalVolume* fPhysVol;
    G4bool fDrawit;

	G4ThreeVector fTimes; //Pick // (global, local, proper)
	int fTrackID; //Pick
};

typedef G4THitsCollection<PandaXPMTHit> PandaXPMTHitsCollection;

extern G4ThreadLocal G4Allocator<PandaXPMTHit>* PandaXPMTHitAllocator;

inline void* PandaXPMTHit::operator new(size_t){
  if(!PandaXPMTHitAllocator)
      PandaXPMTHitAllocator = new G4Allocator<PandaXPMTHit>;
  return (void *) PandaXPMTHitAllocator->MallocSingle();
}

inline void PandaXPMTHit::operator delete(void *aHit){
  PandaXPMTHitAllocator->FreeSingle((PandaXPMTHit*) aHit);
}

#endif
