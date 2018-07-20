//Askaryan.cpp

#include "Askaryan.h"
#include <fftw3.h>
#include <algorithm>
#include <iostream>
#include <numeric>

void Askaryan::setAskTheta(float x){
	_askaryanTheta = x;
}

void Askaryan::setAskFreq(std::vector<float> *x){
	_askaryanFreq = x;
}

void Askaryan::setAskR(float x){
	_askaryanR = x;
}

void Askaryan::setAskE(float x){
	_E = x;
	if(_EM)
	{
		this->emShower();
	}
	else if(_HAD)
	{
		this->hadShower();
	}
	else
	{
		this->hadShower(); //Do something more intelligent here.
	}
}

float Askaryan::getAskE(){
    return _E;
}

std::vector<std::vector<cf> >* Askaryan::E_omega(){}

float Askaryan::criticalF()
{
		return *max_element(_askaryanFreq->begin(),_askaryanFreq->end());
}

float Askaryan::E_t_thetaC(float t)
{	
	std::vector<std::vector<float> > *result = new std::vector<std::vector<float> >;
	std::vector<float> Er_t;
	std::vector<float> Etheta_t;
	std::vector<float> Ephi_t;
	std::vector<float>::iterator i;
	for(i=_times->begin();i!=_times->end();++i)
	{
		Er_t.push_back(0.0);
		Ephi_t.push_back(0.0);
		float E_0 = 4.5e-14 * 1.0e9; //V ns
		float energy_in_TeV = _E/1000.0;
		float t_1 = 0.057; //ns
		float t_2 = 1.0/2.87; //ns
		float t_3 = 0.030;
		float t_4 = 1.0/3.05;
		float a = 3.0;
		float b = 3.5;
		float field_plus = -E_0 * energy_in_TeV * (exp(-std::abs(*i)/t_1)/t_1 + a/t_2*std::pow(1+std::abs(*i)/t_2,-(a+1.0)));
		float field_minus = E_0 * energy_in_TeV * (exp(-std::abs(*i)/t_3)/t_3 + b/t_4*std::pow(1+std::abs(*i)/t_4,-(b+1.0)));
		if(*i > 0) Etheta_t.push_back(field_plus/_askaryanR);
		else Etheta_t.push_back(field_minus/_askaryanR);
	}
	result->push_back(Er_t);
	result->push_back(Etheta_t);
	result->push_back(Ephi_t);
	return result;
}

std::vector<std::vector<float> >* Askaryan::E_t(){
	
	std::vector<std::vector<float> > *E_on_cone = new std::vector<std::vector<float> >;
	E_on_cone = this->E_t_thetaC();
	float C = 1.0e-7*this->getAskR()/sin(acos(COS_THETA_C))/_LQ*sin(_askaryanTheta);

	return result;
}

std::vector<float>* Askaryan::time()
{
	return _times;
}

float Askaryan::getAskR(){
    return _askaryanR;
}

void Askaryan::setIndex(float n){
	INDEX = n;
	COS_THETA_C = 1.0/n;
}

void Askaryan::SetEmHad(bool em,bool had)
{
	_EM = em;
	_HAD = had;
}

void Askaryan::setAskTimes(std::vector<float>* t)
{
	_times = t;
}

void Askaryan::emShower()
{
	float E_CRIT = 0.073; //GeV
	//Greisen EM shower profile from Energy E in GeV.
	std::vector<float> *nx = new std::vector<float>;
	float max_x = 50.0; //maximum number of radiation lengths
	float dx = 0.01; //small enough bin in depth for our purposes.
	float x_start = dx; //starting radiation length
	for(float x=x_start;x<max_x;x+=dx)
	{
		float a = 0.31/sqrt(log(_E/E_CRIT));
		float b = x;
		float c = 1.5*x;
		float d = log((3*x)/(x+2*log(_E/E_CRIT)));
		nx->push_back(a*exp(b-c*d));
	}
	float excess=0.25;
	float LQ = excess*std::accumulate(nx->begin(),nx->end(),0.0);
	delete nx;
	_LQ = LQ;
}

void Askaryan::hadShower()
{
	std::vector<float> *nx = new std::vector<float>;
	float max_x = 2000.0; //maximum depth in g/cm^2
	float dx = 1.0; //small enough bin in depth for our purposes.
	float x_start = dx; //depth in g/cm^2
	float S0 = 0.11842;
	float X0 = 39.562; //g/cm^2
	float lambda = 113.03; //g/cm^2
	float Ec = 0.17006; //GeV
	float Xmax = X0*log(_E/Ec);
	for(float x=x_start;x<max_x;x+=dx)
	{
		float a = S0*_E/Ec*(Xmax-lambda)/Xmax*exp(Xmax/lambda-1);
		float b = pow(x/(Xmax-lambda),Xmax/lambda);
		float c = exp(-x/lambda);
		nx->push_back(a*b*c);
	}
	float excess=0.25;
	float LQ = excess*std::accumulate(nx->begin(),nx->end(),0.0);
	delete nx;
	_LQ = LQ;
}