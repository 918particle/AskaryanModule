//Askaryan.cpp

#include "Askaryan.h"
#include <fftw3.h>
#include <algorithm>
#include <iostream>

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
}

float Askaryan::getAskE(){
    return _E;
}

std::vector<std::vector<cf> >* Askaryan::E_omega()
{
    std::vector<cf> *rComp = new std::vector<cf>;
	std::vector<cf> *thetaComp = new std::vector<cf>;
	std::vector<cf> *phiComp = new std::vector<cf>;
	std::vector<std::vector<cf> > *result = new std::vector<std::vector<cf> >;
	cf zero(0,0);
	std::vector<float>::iterator f;
	for(f=_askaryanFreq->begin();f!=_askaryanFreq->end();++f)
	{
		rComp->push_back(zero);
		phiComp->push_back(zero);
		float zhs_1992_eq_20 = 1.1e-7 * (_E/1000.0) * (*f/0.5) / (1.0+0.4*std::pow(*f/0.5,1.5));
		zhs_1992_eq_20/=_askaryanR;
		float delta_theta = 2.4/((*f)/0.5);
		float theta = _askaryanTheta*180.0/PI;
		float theta_c = acos(COS_THETA_C)*180.0/PI;
		float angular_factor = exp(-0.5*(theta-theta_c)/delta_theta*(theta-theta_c)/delta_theta);
		float phase = PI/2.0*exp(-1.0*(*f)/4.0);
		float real_part = zhs_1992_eq_20*angular_factor*cos(phase);
		float imaginary_part = zhs_1992_eq_20*angular_factor*sin(phase);
		cf result(real_part,imaginary_part); //assumes 90 degree phase
		thetaComp->push_back(result);
	}
	result->push_back(*rComp);
	result->push_back(*thetaComp);
	result->push_back(*phiComp);
	return result;
}

float Askaryan::criticalF()
{
		return *max_element(_askaryanFreq->begin(),_askaryanFreq->end());
}

std::vector<std::vector<float> >* Askaryan::E_t(){
	std::vector<std::vector<cf> > *e = new std::vector<std::vector<cf> >;
	e = E_omega();
	std::vector<cf> e_r = e->at(0);
	std::vector<cf> e_theta = e->at(1);
	std::vector<cf> e_phi = e->at(2);
	delete e;
	float df = criticalF()/(float(e_r.size()));
	df*=1000.0; //now in MHz.
	int n = e_r.size()*2;
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
	for(int i=0;i<n;++i){
		if(i<n/2){
			in1[i][0] = real(e_r[i]);
			in2[i][0] = real(e_theta[i]);
			in3[i][0] = real(e_phi[i]);
			in1[i][1] = imag(e_r[i]);
			in2[i][1] = imag(e_theta[i]);
			in3[i][1] = imag(e_phi[i]);
		}
		else{
			in1[i][0] = real(e_r[n-i-1]);
			in2[i][0] = real(e_theta[n-i-1]);
			in3[i][0] = real(e_phi[n-i+1]);
			in1[i][1] = -1.0*imag(e_r[n-i-1]);
			in2[i][1] = -1.0*imag(e_theta[n-i-1]);
			in3[i][1] = -1.0*imag(e_phi[n-i-1]);
		}
	}
	fftw_execute(p1);
	fftw_execute(p2);
	fftw_execute(p3);
	std::vector<std::vector<float> > *result = new std::vector<std::vector<float> >;
	std::vector<float> Er_t;
	std::vector<float> Etheta_t;
	std::vector<float> Ephi_t;
	for(int i=0;i<n;++i)
	{
		//Output the real part.  It has been verified that the imaginary
		//part is zero, meaning all the power is present in Re{E(t)}.
		//We must multiply the result by df in MHz, because the IFFT is
		//computed discretely, without the frequency measure.  This
		//changes the final units from V/m/MHz to V/m vs. time.
		Er_t.push_back(out1[i][0]*df);
		Etheta_t.push_back(out2[i][0]*df);
		Ephi_t.push_back(out3[i][0]*df);
	}
	//Note: The choice of sign in the Fourier transform convention should not determine physical
	//properties of the output.  The following code ensures the correct physical timing, according
	//to the RB paper, and that the either choice of convention produces the same answer.
	if(FFTW_CHOICE=="FFTW_BACKWARD"){
		std::reverse(Er_t.begin(),Er_t.end());
		std::reverse(Etheta_t.begin(),Etheta_t.end());
		std::reverse(Ephi_t.begin(),Ephi_t.end());
	}
	result->push_back(Er_t);
	result->push_back(Etheta_t);
	result->push_back(Ephi_t);
	return result;
}

std::vector<float>* Askaryan::time()
{
	float fc = criticalF();
	float dt = 1.0/(2.0*fc);
	int n = 2*_askaryanFreq->size();
	std::vector<float> *result = new std::vector<float>;
	for(int i=0;i<n;++i) result->push_back(float(i)*dt);
	return result;
}

float Askaryan::getAskR(){
    return _askaryanR;
}

void Askaryan::setIndex(float n){
	INDEX = n;
	COS_THETA_C = 1.0/n;
}