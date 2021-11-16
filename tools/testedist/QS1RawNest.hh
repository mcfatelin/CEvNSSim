#ifndef QS1RAWNEST_HH
#define QS1RAWNEST_HH

#include <TRandom3.h>
#include <TVector3.h>
#include <TF1.h>
#include <TH1I.h>

#ifndef ENUM_PRECOILTYPE
#define ENUM_PRECOILTYPE
typedef enum { rtNR, rtER } PRecoilType;
#endif // ENUM_PRECOILTYPE


class QS1RawNest 
{
	public:
		QS1RawNest();
		~QS1RawNest() {};
		
		static Int_t GetQuanta(Double_t de, Double_t fs, PRecoilType rt, Bool_t rf=false);
		static TH1I* GenTimingProfile(Int_t np, PRecoilType rt=PRecoilType::rtNR, Double_t nf=1.);
		static TVector3 GenAbsolutePosition(const Double_t r, const Double_t hmin, const Double_t hmax); // cylindrical region, origin at (0,0)

		static std::vector<Int_t> GenTimingPhoton(const TH1I* const h);
		static std::vector<TVector3> GenUniformDirection(Int_t np); // generate uniformly directional distribution

		static Int_t GetMaxTime() { return _MAX_DECAYTIME; }
		
	private:
		static const Double_t _MEAN_WF_ENERGY;	// scintillation mean work function energy
		static const Double_t _LIQUID_DENSITY;	// g/cm3 // for liquid xenon at b.p., wikipedia
		static const Int_t _MAX_DECAYTIME; // ns

		// for GetQuanta(...)
		static Double_t GetLinhardFactor(const Double_t deposit_energy);
		static Double_t GetExcitationRatio(const Double_t deposit_energy, const Double_t field_strength, const PRecoilType recoil_type);
		static Double_t GetRecombinationRate(const Double_t deposit_energy, const Double_t field_strength, const PRecoilType recoil_type, const Int_t numof_ionization);		

		static TRandom3 _rr, _ra, _rz;

};


#endif // QS1RAWNEST_HH
