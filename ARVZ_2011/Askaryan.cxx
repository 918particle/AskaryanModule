//Askaryan.cpp

#include "Askaryan.h"
#include <fftw3.h>
#include <algorithm>
#include <iostream>
#include <numeric>

void Askaryan::setAskTheta(float x)
{
	_askaryanTheta = x;
}

void Askaryan::setAskFreq(std::vector<float>* x)
{
	_askaryanFreq = x;
}

void Askaryan::setAskR(float x)
{
	_askaryanR = x;
}

void Askaryan::setAskE(float x)
{
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

std::vector<std::vector<cf> >* Askaryan::E_omega()
{
	std::vector<std::vector<float> > *e = new std::vector<std::vector<float> >;
	e = E_t();
	std::vector<float> e_r = e->at(0);
	std::vector<float> e_theta = e->at(1);
	std::vector<float> e_phi = e->at(2);
	delete e;
	float dt = (this->time()->at(1)-this->time()->at(0))/1000.0; //microseconds
	int n = e_r.size();
	fftw_complex *in1,*in2,*in3,*out1,*out2,*out3;
	in1 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*n);
	in2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*n);
	in3 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*n);
	out1 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*n);
	out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*n);
	out3 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*n);
	fftw_plan p1,p2,p3;
	if(FFTW_CHOICE=="FFTW_BACKWARD")
	{
		p1 = fftw_plan_dft_1d(n,in1,out1,1,FFTW_ESTIMATE);
		p2 = fftw_plan_dft_1d(n,in2,out2,1,FFTW_ESTIMATE);
		p3 = fftw_plan_dft_1d(n,in3,out3,1,FFTW_ESTIMATE);
	}
	else
	{
		p1 = fftw_plan_dft_1d(n,in1,out1,-1,FFTW_ESTIMATE);
		p2 = fftw_plan_dft_1d(n,in2,out2,-1,FFTW_ESTIMATE);
		p3 = fftw_plan_dft_1d(n,in3,out3,-1,FFTW_ESTIMATE);
	}
	//Proper assignment to input transforms
	for(int i=0;i<n;++i)
	{
		in1[i][0] = e_r[i];
		in2[i][0] = e_theta[i];
		in3[i][0] = e_phi[i];
		in1[i][1] = 0.0;
		in2[i][1] = 0.0;
		in3[i][1] = 0.0;
	}
	fftw_execute(p1);
	fftw_execute(p2);
	fftw_execute(p3);
	std::vector<std::vector<cf> > *result = new std::vector<std::vector<cf> >;
	std::vector<cf> Er;
	std::vector<cf> Etheta;
	std::vector<cf> Ephi;
	for(int i=0;i<n/2;++i)
	{
		//Output the complex FFT.  It has been verified that the imaginary
		//part is zero, meaning all the power is present in Re{E(t)}.
		//We must multiply the result by dt in microseconds, so the units
		//are V/m/MHz.
		Er.push_back(cf(out1[i][0]*dt*NORM,out1[i][1]*dt*NORM));
		Etheta.push_back(cf(out2[i][0]*dt*NORM,out2[i][1]*dt*NORM));
		Ephi.push_back(cf(out3[i][0]*dt*NORM,out3[i][1]*dt*NORM));
	}
	result->push_back(Er);
	result->push_back(Etheta);
	result->push_back(Ephi);
	return result;
}

float Askaryan::criticalF()
{
		return *max_element(_askaryanFreq->begin(),_askaryanFreq->end());
}

float Askaryan::FormFactor(float t)
{	
	float E_0 = 4.5e-14; //V s
	float energy_in_TeV = _E/1000.0;
	float t_1 = 0.057; //ns
	float t_2 = 1.0/2.87; //ns
	float t_3 = 0.030;
	float t_4 = 1.0/3.05;
	float a = 3.0;
	float b = 3.5;
	float A_plus = -E_0 * energy_in_TeV * (exp(-std::abs(t)/t_1) + std::pow(1+std::abs(t)/t_2,-a));
	float A_minus = -E_0 * energy_in_TeV * (exp(-std::abs(t)/t_3) + std::pow(1+std::abs(t)/t_4,-b));
	if(t > 0) return 1.0e7/sin(acos(COS_THETA_C))/_LQ*A_plus;
	else return 1.0e7/sin(acos(COS_THETA_C))/_LQ*A_minus;
}

float Askaryan::A_t(float t)
{	
	float result = 0.0;
	float C = 1.0e-7/_askaryanR*sin(_askaryanTheta);
	if(_EM)
	{
		float E_CRIT = 0.073; //GeV
		//Greisen EM shower profile from Energy E in GeV.
		std::vector<float> *nx = new std::vector<float>;
		float max_x = 50.0; //maximum number of radiation lengths
		float dx = 0.02; //small enough bin in depth for our purposes.
		float x_start = dx; //starting radiation length
		for(float x=x_start;x<max_x;x+=dx)
		{
			float a = 0.31/sqrt(log(_E/E_CRIT));
			float b = x;
			float c = 1.5*x;
			float d = log((3*x)/(x+2*log(_E/E_CRIT)));
			float t_prime = t-x*ICE_RAD_LENGTH/ICE_DENSITY*(1.0/LIGHT_SPEED-INDEX*cos(_askaryanTheta)/LIGHT_SPEED)*PSF;
			nx->push_back(a*exp(b-c*d)*this->FormFactor(t_prime));
		}
		float excess=0.25;
		result = C*ICE_RAD_LENGTH/ICE_DENSITY*dx*excess*std::accumulate(nx->begin(),nx->end(),0.0);
		delete nx;
	}
	else if(_HAD)
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
		float excess=0.25;
		for(float x=x_start;x<max_x;x+=dx)
		{
			float a = S0*_E/Ec*(Xmax-lambda)/Xmax*exp(Xmax/lambda-1);
			float b = pow(x/(Xmax-lambda),Xmax/lambda);
			float c = exp(-x/lambda);
			float t_prime = t-x/ICE_DENSITY*(1.0/LIGHT_SPEED-INDEX*cos(_askaryanTheta)/LIGHT_SPEED)*PSF;
			nx->push_back(a*b*c*this->FormFactor(t_prime));
		}
		result = C*dx/ICE_DENSITY*excess*std::accumulate(nx->begin(),nx->end(),0.0);
		delete nx;
	}
	else
	{
		result = -3.14159; //Do something more intelligent here.
	}
	return result;
}

std::vector<std::vector<float> >* Askaryan::E_t()
{
	std::vector<float> *eTheta = new std::vector<float>;
	std::vector<float> *ePhi = new std::vector<float>;
	std::vector<float> *eR = new std::vector<float>;
	eTheta->clear();
	std::vector<float>::iterator i;
	std::vector<float>::iterator j;
	for(i=this->time()->begin(),j=this->time()->begin()+1;i!=this->time()->end(),j!=this->time()->end();++i,++j)
	{
		//Two-point derivative for E(t) from A(t)
		eTheta->push_back(-1.0*(this->A_t(*j)-this->A_t(*i))/((*j)-(*i))*1.0e9*0.5); //Units: V/m...note the factor of 2
		ePhi->push_back(0.0);
		eR->push_back(0.0);
	}
	std::vector<std::vector<float> > *result = new std::vector<std::vector<float> >;
	result->push_back(*eR);
	result->push_back(*eTheta);
	result->push_back(*ePhi);
	delete eR;
	delete eTheta;
	delete ePhi;
	return result;
}

std::vector<float>* Askaryan::time()
{
	return _times;
}

float Askaryan::getAskR()
{
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

std::vector<float>* Askaryan::getAskFreq()
{
	return _askaryanFreq;
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
	//Explanation of units: the integral is meant to be of charge versus density.  The Q(z) is actually a function of
	//number of radiation lengths, so the integral must be scaled by ICE_RAD_LENGTH/ICE_DENSITY, or the distance of 
	//one radiation length in ice.  This way the units work out to be Coulombs x meters.
	float excess=0.25;
	float LQ = ICE_RAD_LENGTH/ICE_DENSITY*dx*excess*std::accumulate(nx->begin(),nx->end(),0.0);
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
	float excess=0.25;
	for(float x=x_start;x<max_x;x+=dx)
	{
		float a = S0*_E/Ec*(Xmax-lambda)/Xmax*exp(Xmax/lambda-1);
		float b = pow(x/(Xmax-lambda),Xmax/lambda);
		float c = exp(-x/lambda);
		nx->push_back(a*b*c);
	}
	//Explanation of units: the integral is meant to be of charge versus density.  The Q(z) is actually a function of
	//radiation length, so the integral must be scaled by 1,0/ICE_DENSITY, so the units work out to be Coulombs x meters.
	float LQ = dx/ICE_DENSITY*excess*std::accumulate(nx->begin(),nx->end(),0.0);
	delete nx;
}