#ifndef QUANTANEST_H
#define QUANTANEST_H

#include <TRandom3.h>

class QuantaNest {

public:
  QuantaNest ();
  ~QuantaNest () {}

  void calculate();

  int getNElectron();
  int getNPhoton();

  double getLightPE();
  double getChargePE();

  void setEnergy(double e);

  void setField(double f);

  void setType (int t);

  void setDensity (double d);

  double getLindhardFactor ();

  int getNQuanta ();

  int getNIonization ();

  int getNExcitation ();

  double getRatio ();

  double getRecombinationRate();

  double getRecombinationRateT();

  void setPmtResolution (double r);

  void setDpeFraction (double f);

  void setPDE (double p);

  void setEEE (double e);

  void setGasGain (double g);

  void setRecombFluctuation (bool t);
private:
  void calculateNQuanta();
  void calculateNexNi ();
  void calculateNexNiRatio ();
  void calculateRecombinationRate();
  void calculateErRecombinationRate();
  void calculatePhotonElectron();
  void calculateCharge();
  void calculateF0F1F2();
  // parameters for input/output
  double energy;
  double field;

  int type;

  int nElectron;
  int nPhoton;

  double lightPE;
  double chargePE;

  double density;

  // parameters used in the calculation
  double lindhardFactor;
  double epsilon;
  double gamma;
  double kappa;

  double resolution;            // for quanta generation
  int nQuanta;                  // number of quanta generated
  double ratio;                 // ratio of intial Nex/Ni
  int nIonization;              // number of initial ionization
  int nExcitation;              // number of initial excitation

  double zeta;
  double recombinationRate;     // rate of recombination
  double recombinationRate_t;	// rate of combination without fluctuation
  double lightQuenching;        // quenching factor for light
  //static const double W = 13.7; // work function, 13.7 eV
  static const double W; // work function, 13.7 eV

  double pmtResolution;		// resolution of PMT
  double dpeFraction;		// fraction of double photon emission
  double pde;			// photon detection efficiency
  double eee;			// electron extraction efficiency
  double f0;			// detection inefficiency of photon
  double gasGain;		// gain of gas

  bool recombFluctuation;       // control whether to use the fluctuation of recombination
  
  TRandom3 tr;
  
};

#endif // QUANTANEST_H
