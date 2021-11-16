#include "GeometryFactor.h"
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

#include <TVector3.h>

#define DEBUG_SOLID_ANGLE

//const Double_t PMT_RADIUS=76./2;
const Double_t PMT_RADIUS=64./2;

//---------------------------------------------------------------------
// Geometrical factor (solid angle) of circular disc at the end circles
// subtended by a cylindrical detector at an internal point source. 
//---------------------------------------------------------------------
// Creater:	Parinya Namwongsa
// Created:	2018/02/03
// Email:	pickitsimple@gmail.com, pickitsimple@hotmail.com
//---------------------------------------------------------------------
// Tools: GSL QAWO integration under ROOT
// Input: PMT radius, PMT vertex, event vertex
// Output: Geometry Factor (Solid Angle) of the PMT by the event
//---------------------------------------------------------------------
// Usage: GeometryFactor::Calculate(GeometryFactor::subtend(src_pos, pmt_pos));
//---------------------------------------------------------------------
// References: Tsoulfanidis, "Measurement and Detection of Radiation".


Double_t GeometryFactor::f(Double_t x, void * params) {
  param para = *(param *) params;
  Double_t numerator = para.Rd*para.Rd - para.r*para.r - para.d*para.d*tan(x)*tan(x);
  Double_t denominator = 2*para.r*para.d*tan(x);
  Double_t phi = acos(numerator/denominator);
  Double_t f = 2*(M_PI - phi);
  return f;
}


GeometryFactor::GeometryFactor(size_t level_)
 : _F(new gsl_function), _result(0.), _omega(0.), _error(0.), _epsabs(0.)
 , _epsrel(1e-7), _w(gsl_integration_workspace_alloc(level_))
{
  _F->function = &f;
}

GeometryFactor::~GeometryFactor()
{
	gsl_integration_workspace_free (_w);
	delete _F;
}


param GeometryFactor::subtend(TVector3 source_, TVector3 pmt_)
{
	//param result = {.r=0., .d=650., .Rd=PMT_RADIUS};
	param result = {0., 0., PMT_RADIUS};
	
	result.r = sqrt((source_.X()-pmt_.X())*(source_.X()-pmt_.X()) + (source_.Y()-pmt_.Y())*(source_.Y()-pmt_.Y()));
	result.d = abs(source_.Z() - pmt_.Z());
	
	return result;
}

Double_t GeometryFactor::Calculate(param para_, const size_t level_)
{
  const Double_t theta2 = atan((para_.r+para_.Rd)/para_.d);
  const Double_t theta1 = atan(abs(para_.r-para_.Rd)/para_.d);
  const Double_t L = theta2 - theta1;
  const Double_t omg = 1.; //mm (internal omega)
  
  //Double_t expected = 0.;

  if (para_.r >= para_.Rd)
  {
	auto wt = gsl_integration_qawo_table_alloc (omg, L, GSL_INTEG_SINE, level_); 	// !!! this alloc can be moved into the constructor in case of performance incresing. #Pick
	gsl_integration_qawo_table_set_length(wt, L);
	_F->params = &para_;
	gsl_integration_qawo(_F, theta1, _epsabs, _epsrel, level_, _w, wt, &_result, &_error);
	gsl_integration_qawo_table_free (wt);
  }

  
  const Double_t omega1 = (para_.r >= para_.Rd) ? 0 : 2*M_PI*(1-cos(theta1));
  const Double_t omega2 = _result;
  const Double_t _omega = omega1 + omega2; 
  const Double_t gf = _omega/(4*M_PI);		// geometric factor
  
#ifdef DEBUG_SOLID_ANGLE
  printf ("theta2          = % .18f\n", theta2);
  printf ("theta1          = % .18f\n", theta1);
  printf ("result          = % .18f\n", _result);
  //printf ("exact result    = % .18f\n", expected);
  printf ("estimated error = % .18f\n", _error);
  //printf ("actual error    = % .18f\n", result - expected);
  printf ("intervals       = %zu\n", _w->size);
  printf ("omega1          = % .18f\n", omega1);
  printf ("omega2          = % .18f\n", omega2);
  printf ("omega           = % .18f\n", _omega);
  printf ("gf              = % .18f\n", gf);
#endif
  return gf;
}

double GeometryFactor::Calculate(const std::vector<TVector3> &pmt_pos_
  , TVector3 src_pos_, const size_t level_)
{
	Double_t geosum = 0.;
	for (auto i : pmt_pos_)
	{
#ifdef DEBUG_SOLID_ANGLE
		printf("******************* PMT: x=%f, y=%f, z=%f\n", i.X(), i.Y(), i.Z());

#endif
		geosum += GeometryFactor::Calculate(GeometryFactor::subtend(src_pos_, i), level_);
	}

	return geosum;
}


