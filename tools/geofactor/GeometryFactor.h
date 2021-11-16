#ifndef GeometryFactor_H
#define GeometryFactor_H
#include <gsl/gsl_integration.h>

class TVector3;

extern const Double_t PMT_RADIUS;

struct param
{
	Double_t r;	// relative distance between two alignment x-y planes, x-y direction
	Double_t d;	// distance between event and PMT x-y plane, z-direction
	Double_t Rd;	// radius of diafram (radius of PMT)
};

class GeometryFactor
{
public:
	GeometryFactor(size_t level_=100);
	~GeometryFactor();
	
	static param subtend(TVector3 source_, TVector3 pmt_);
	double Calculate(param para_ = { .r=0., .d=650., .Rd=PMT_RADIUS}, const size_t level_=100);
	double Calculate(const std::vector<TVector3> &pmt_pos_, TVector3 src_pos_, const size_t level_=100);
	
	Double_t GetOmega() { return _omega; }
private:
	static Double_t f(Double_t x, void * params);
	
	gsl_function* _F;
	gsl_integration_workspace* _w;
	
	Double_t _omega;
	Double_t _result;
	Double_t _error;
	Double_t _epsabs;
	Double_t _epsrel;

};

#endif //GeometryFactor_H
