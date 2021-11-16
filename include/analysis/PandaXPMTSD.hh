#ifndef PandaXPMTSD_h
#define PandaXPMTSD_h 1

#include "G4DataVector.hh"
#include "G4VSensitiveDetector.hh"
#include "analysis/PandaXPMTHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class PandaXPMTSD : public G4VSensitiveDetector
{

  public:

    PandaXPMTSD(G4String name);
    virtual ~PandaXPMTSD();
 
    virtual void Initialize(G4HCofThisEvent* );
    virtual bool ProcessHits(G4Step* aStep, G4TouchableHistory* );
 
    //A version of processHits that keeps aStep constant
    bool ProcessHits_constStep(const G4Step* ,
                                 G4TouchableHistory* );
    virtual void EndOfEvent(G4HCofThisEvent* );
 
    //Initialize the arrays to store pmt possitions
    inline void InitPMTs(int nPMTs){
      if(fPMTPositionsX)delete fPMTPositionsX;
      if(fPMTPositionsY)delete fPMTPositionsY;
      if(fPMTPositionsZ)delete fPMTPositionsZ;
      fPMTPositionsX=new G4DataVector(nPMTs);
      fPMTPositionsY=new G4DataVector(nPMTs);
      fPMTPositionsZ=new G4DataVector(nPMTs);
    }

    //Store a pmt position
    void SetPmtPositions(const std::vector<G4ThreeVector>& positions);

  private:

    PandaXPMTHitsCollection* fPMTHitCollection;

    G4DataVector* fPMTPositionsX;
    G4DataVector* fPMTPositionsY;
    G4DataVector* fPMTPositionsZ;
};

#endif
