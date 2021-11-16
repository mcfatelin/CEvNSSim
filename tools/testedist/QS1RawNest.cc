#include "QS1RawNest.hh"

#include <TMath.h>

using namespace std;

//#define _DEBUG_NEST

const Double_t QS1RawNest::_MEAN_WF_ENERGY = 13.7;	// scintillation mean work function energy
const Double_t QS1RawNest::_LIQUID_DENSITY = 2.942;	// g/cm3 // for liquid xenon at b.p., wikipedia

const Int_t QS1RawNest::_MAX_DECAYTIME = 100; // ns

TRandom3 QS1RawNest::_rr(0);
TRandom3 QS1RawNest::_ra(0);
TRandom3 QS1RawNest::_rz(0);
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// --------------------------------------------------------------------

QS1RawNest::QS1RawNest()
{
	// Created: PQuantaNest: 2016-12-21, Parinya Namwongsa, SUT Thailand	
	// Modified to be: QS1RawNest: 2018-02-21, Parinya Namwongsa, SJTU China	
}

std::vector<TVector3> QS1RawNest::GenUniformDirection(Int_t np)
{
	TRandom3 rd(0), rz(0);
	vector<TVector3> v;

	for (Int_t i=0; i<np; i++)
	{
		Double_t x=0, y=0;
		rd.Circle(x,y,1);
		
		v.push_back(TVector3(x, y, rz.Rndm()));
	}

	return v;
	
}

TVector3 QS1RawNest::GenAbsolutePosition(const Double_t rmax, const Double_t hmin, const Double_t hmax)
{
	//TRandom3 rr(0), ra(0), rz(0);
	
	const Double_t r = _rr.Rndm()*rmax*rmax;
	const Double_t angle = _ra.Rndm()*2*M_PI;
	
	return TVector3(std::sqrt(r)*std::cos(angle), 
						 std::sqrt(r)*std::sin(angle), 
						 _rz.Rndm()*(hmax-hmin) + hmin);
}

std::vector<Int_t> QS1RawNest::GenTimingPhoton(const TH1I* const h)
{
	vector<Int_t> t;
	
	for (Int_t i=0; i<h->GetNbinsX(); i++)
		if (h->GetBinContent(i+1) > 0)
			for (Int_t j=0; j<h->GetBinContent(i+1); j++)
				t.push_back(i);	// time bin (nano second)
	
	return t;
}

TH1I* QS1RawNest::GenTimingProfile(const Int_t np, const PRecoilType rt, const Double_t nf)
{
	auto h = new TH1I("tq", "photon timing profile", QS1RawNest::GetMaxTime(), 0, QS1RawNest::GetMaxTime());
	// Modeling Pulse Characteristics in Xenon with NEST
	// J.Mock et. all

	auto f = new TF1("_TIME_PDF", "((([0]/[2])*TMath::Exp(-(x/[2]))) + (([1]/[3])*TMath::Exp(-(x/[3]))))*[4]", 0, _MAX_DECAYTIME);
	
	// !!! FLUCTUATION STILL NOT FINISH
	const Double_t t1 = 3.10; // ns, Singlet lifetime (fast component)
	//const Double_t t1sigma = 0.7;
	const Double_t t2 = 24.0; // ns, Triplet lifetime (slow component)
	//const Double_t t2sigma = 1.0;
	//const Double_t nf = 1.00; // normalization factor
	
	// Singlet/Triplet - ER (gamma induced)
	const Double_t f1er = 0.2; // ns, directed excitation
	const Double_t f2er = 0.8; // ns, recombination
	
	// Singlet/Triplet - NR (neutron induced) = 7.8 (+-1.5)
	// f2nr = 1 / 7.8
	// f1nr = 1 - f2nr
	const Double_t f2nr = 0.128;
	const Double_t f1nr = 0.872;
	
	if (rt == PRecoilType::rtNR)
	{
		f->SetParameters(f1nr, f2nr, t1, t2, nf);
		f->SetTitle("NR J.Mock2014");
		f->SetLineColor(kRed);
	}
	else
	{
		f->SetParameters(f1er, f2er, t1, t2, nf);
		f->SetTitle("ER J.Mock2014");
		f->SetLineColor(kBlue);
	}

	h->FillRandom("_TIME_PDF", np);
	
	delete f;
	return h;
}

Int_t QS1RawNest::GetQuanta(const Double_t de, const Double_t fs, const PRecoilType rt, const Bool_t rf) 
{
	// de = keV
	// field_strengh = V/cm
	TRandom3 rd(0);

	// get mean number of quanta
	const Double_t mq = (de * 1000) / _MEAN_WF_ENERGY;

	#ifdef _DEBUG_NEST
	cout <<"*** DEBUG QS1RawNest ***" << endl;
	
	if (rt == PRecoilType::rtNR)
		cout << "NR(" << mq << ")" << endl;
	else if (rt == PRecoilType::rtER)
		cout << "ER(" << mq << ")" << endl;
	else
		cout << "--" << endl;
	#endif

	// get number of quanta from the normal distribution of the detection resolution
	Int_t nq = rd.Gaus(mq, TMath::Sqrt(mq * ((0.12724-0.032152*_LIQUID_DENSITY - 0.0013492*TMath::Power(_LIQUID_DENSITY, 2.0))*1.5)));

	#ifdef _DEBUG_NEST
	cout << "nq = " << nq << endl;	
	#endif
	
	// the number of quanta of the NR events also affected by the Linhard's factor
	if (rt == PRecoilType::rtNR)
	{
		const Double_t lf = QS1RawNest::GetLinhardFactor(de);
		const Double_t slf = rd.Gaus(lf, 0.25*lf);
		nq = rd.Binomial(nq, slf);
		if (nq < 0) nq = 0;

		#ifdef _DEBUG_NEST
		cout << "lf = " << nq << endl;	
		cout << "slf = " << slf << endl;	
		#endif

	}

	#ifdef _DEBUG_NEST
	cout << "nq = " << nq << " (after NR Linhard's factor)" << endl;	
	#endif
	
	// evaluate the number of excitation quanta (exciton)
	// evaluate the number of ionization quanta (ion)
	Int_t ni = 0;
	Int_t ne = 0;
	if (nq > 0)
	{
		const Double_t er = QS1RawNest::GetExcitationRatio(de, fs, rt);
		ne = rd.Binomial(nq, er/(1+er));
		ni = nq - ne;
		#ifdef _DEBUG_NEST
		cout << "er = " << er << endl;		
		cout << "nr = " << ne << endl;	
		cout << "ni = " << ni << endl;	
		#endif
	}

	// evaluate the recombination rate
	// 0 < rr < 1
	Double_t rr = QS1RawNest::GetRecombinationRate(de, fs, rt, ni);
	#ifdef _DEBUG_NEST
	cout << "rr = " << rr << endl;	
	#endif
	if (rf == true)
	{
		const Double_t rr_t = rr;
		
		while(1)
		{
			rr = rd.Gaus(rr_t, TMath::Sqrt(0.0056 * ni * rr_t));
			if (rr < 1)	break;
		}
	}
	if (rr < 0) rr = 0;

	#ifdef _DEBUG_NEST
	if (rf == true)
		cout << "rr = " << rr << " (after recombination fluctuation)" << endl;	
	#endif
	
	// evaluate the number of S1 photons
	// S1 = S1(scintillation) + S1(recombination)
	Int_t np = 0;
	if (rf == true)
		np = ne + (int) (ni * rr);
	else
		np = ne + rd.Binomial(ni, rr);

	#ifdef _DEBUG_NEST
	cout << "np = " << np << endl;	
	#endif


	// evaluate the number of escape electrons
	Int_t nee =  nq - np;

	#ifdef _DEBUG_NEST
	cout << "nee = " << nee << endl;	
	#endif


	// the number of S1 photons also affected by scintillation quenching
	if (rt == PRecoilType::rtNR)
	{
		const Double_t epsilon = 11.5 * de * TMath::Power(54, -7.0/3.0);
		const Double_t sq = 1.0/(1 + 3.3 * TMath::Power(epsilon, 1.14));
		np = rd.Binomial(np, sq);

		#ifdef _DEBUG_NEST
		cout << "sq = " << sq << endl;	
		cout << "np = " << np << " (after NR scintillation quenching)" << endl;	
		#endif
	}	

	// evaluate the number of S2 PE charges
	// LATER
	
	//return TVector3(np, nee, 0); // return (S1, Escape Electron, S2);
	return np; // return S1 RAW (Photon)
}

Double_t QS1RawNest::GetLinhardFactor(const Double_t de) 
{
	const Double_t epsilon = 11.5 * de * TMath::Power(54, -7.0/3.0);
	const Double_t gamma = 3 * TMath::Power(epsilon, 0.15) + 0.7 * TMath::Power(epsilon, 0.6) + epsilon;
	const Double_t kappa = 0.1394;
	return kappa * gamma / (1 + kappa * gamma);

}

Double_t QS1RawNest::GetExcitationRatio(const Double_t de, const Double_t fs, const PRecoilType rt) 
{

	if (rt == PRecoilType::rtNR)
	{
		const Double_t epsilon = 11.5 * de * TMath::Power(54, -7.0/3.0);
		return 1.24 * TMath::Power(fs, -0.0472) * (1 - TMath::Exp(-239*epsilon));
	}
	else if (rt == PRecoilType::rtER)
		return 0.059813 + 0.031228 * _LIQUID_DENSITY;
	else
		return 0.0;
}

Double_t QS1RawNest::GetRecombinationRate(const Double_t de, const Double_t fs, const PRecoilType rt, const Int_t ni) 
{
	Double_t rr = 0.0;
		
	if (ni > 0)
	{
		const Double_t zeta = 0.01385 * TMath::Power(fs, -0.062);

		if (rt == PRecoilType::rtNR)
			rr = 1 - TMath::Log(1 + ni*zeta)/(ni*zeta);
		else if (rt == PRecoilType::rtER)
		{
			double tibF = 0.6347 * TMath::Exp(-0.00014 * fs);
			double tibE = -0.373 * TMath::Exp(-(fs*0.001)/tibF) + 1.5;
			double tibCurlA = 10 * TMath::Power(fs, -0.04) * TMath::Exp(18/fs);
			double tibCurlZ = 1 - TMath::Power(fs, 0.2147) + 3;
			double tomasImel = tibF * TMath::Power(de, -tibE) * (1 - TMath::Exp(-TMath::Power((de - tibCurlZ)/tibCurlA, 0.188 * TMath::Power(fs, 1./3)))) * TMath::Power(_LIQUID_DENSITY/2.888, 0.3);
			rr = 1 - TMath::Log(1 + tomasImel/4.0*ni)/(tomasImel/4.0*ni);
		}
	}
	
	return rr;
}

