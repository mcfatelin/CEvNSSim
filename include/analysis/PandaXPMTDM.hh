#ifndef PANDAXPMTDM_H
#define PANDAXPMTDM_H

#include "analysis/PandaXPMTRunAction.hh"

#include <map>
#include <string>
#include <vector>

class TFile;
class TTree;

class G4Event;

class TemporaryPMTParticle {
  public:
    TemporaryPMTParticle();
    ~TemporaryPMTParticle();

    const std::string &getParticleType() const;
    void setParticleType(const std::string type);

    int getId() const;
    void setId(int i);

    double getEnergy() const;
    void setEnergy(double e);

    double getPx() const;
    void setPx(double v);

    double getPy() const;
    void setPy(double v);

    double getPz() const;
    void setPz(double v);

    double getX() const;
    void setX(double v);

    double getY() const;
    void setY(double v);

    double getZ() const;
    void setZ(double v);

    double getT() const;
    void setT(double v);

  private:
    std::string _type;
    int _id;
    double _energy;
    double _px;
    double _py;
    double _pz;
    double _x;
    double _y;
    double _z;
    double _t;
};

class PandaXPMTDM {

    friend class PandaXPMTRunAction;
    friend class PandaXPMTEventAction;
    friend class PandaXPMTAnalysis;

public:
    PandaXPMTDM(bool enablePMT=true);

    ~PandaXPMTDM();

    void book(const std::string &name = "pandaxout.root");

    void save();

    void saveNullEvent(bool t);

    void fillEvent(const G4Event *aEvent, bool partial = false);

    std::map<int, std::string> &getTrackMap();

    static PandaXPMTDM *Instance();

    void addTemporaryPMTParticle(const TemporaryPMTParticle &tp);
    
    std::vector<std::string> killerProcess;
    std::vector<std::string> prekillerProcess;
    std::vector<std::string> lastTouchableVolume;
    std::vector<std::string> lastStepPreVol;
    std::vector<std::string> lastStepPostVol;
    std::vector<double> lastStepLength;
    std::vector<double> lastStepEdep;
    std::vector<int> opBoundStatus;

  private:
    void resetData();

    //! reset the hits collection of the event
    void resetPartialEvent(const G4Event *aEvent);

    TFile *_rootFile;
    TTree *_mcTree;

    int _runId;
    int _eventId;
    int64_t seed_;

    //variables for PMT
    int _nPMTHits;
    std::vector<std::string > PMTSet;
    std::vector<int> _fPmtNumber;
    std::vector<int> _fPhotons;
    std::vector<double> _fPosX;
    std::vector<double> _fPosY;
    std::vector<double> _fPosZ;
    std::vector<double> _fTimeGlo;	//Pick - detection time
    std::vector<double> _fTimeLoc;	//Pick - distribution time
    std::vector<double> _fTimePro;	//Pick
    //std::vector<double> _fTimeDet;	//Pick
    std::vector<double> _fTrackID;	//Pick
    
    // variables for primary particle
    int _nPrimaries;
    std::vector<std::string> _primaryType;
    std::vector<int> _primaryId;
    std::vector<double> _primaryEnergy;
    std::vector<double> _primaryPx;
    std::vector<double> _primaryPy;
    std::vector<double> _primaryPz;
    std::vector<double> _primaryX;
    std::vector<double> _primaryY;
    std::vector<double> _primaryZ;
    std::vector<double> _primaryT;	// time to decay

    bool _recordPMT;
    bool _saveNullEvent;
    bool _partialSaved;

    std::vector<TemporaryPMTParticle> _particles;
    std::vector<TemporaryPMTParticle> _tparticles;

    std::map<int, std::string> _trackMap;

    static PandaXPMTDM *_instance;
};
#endif
