#ifndef QuantaNestGPSGenerator_H
#define QuantaNestGPSGenerator_H

#include "generator/BambooGenerator.hh"
#include "generator/BambooGeneratorFactory.hh"
#include "generator/QS1RawNest.hh"
#include <G4ThreeVector.hh>

class G4ParticleGun;
class G4Event;

//class TFile;

class QuantaNestGPSGenerator : public BambooGenerator {
public:
    QuantaNestGPSGenerator(const G4String &name);

    ~QuantaNestGPSGenerator();

    virtual void GeneratePrimaries(G4Event *anEvent);

    static GeneratorRegister<QuantaNestGPSGenerator> reg;

private:
    G4ParticleGun* _particleGun;
    
    G4double _Edep;
    G4double _Efield;
    
    G4ThreeVector _Pos;
    
	PRecoilType _rType;
	//TFile* _File;

	static Double_t getNormalizedCrossSection(G4double theta);
	static Double_t getNormalizedFlux(G4double theta);
	static Double_t getRandomTheta();
	static Double_t getRandomTranslation(G4double theta);
	static Double_t getRandomEnergy(G4double theta, G4double lower, G4double upper);
	
};
#endif // QuantaNestGPSGenerator_H
