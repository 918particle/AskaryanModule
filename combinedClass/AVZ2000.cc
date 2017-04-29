//Askaryan.cpp

#include "Askaryan.h"
#include "AVZ2000.h"
#include <fftw3.h>
#include <algorithm>
#include <cmath>

std::vector<std::vector<cf> >* AVZ2000::E_omega(){
    std::vector<cf> *rComp = new std::vector<cf>;
	std::vector<cf> *thetaComp = new std::vector<cf>;
	std::vector<cf> *phiComp = new std::vector<cf>;
	std::vector<float>::iterator j;
    for(j=_askaryanFreq->begin();j!=_askaryanFreq->end();++j)
    {
    	cf complexZero(0.0,0.0);
    	rComp->push_back(complexZero);
    	phiComp->push_back(complexZero);
    	//Remember: _E is in GeV, so we must convert to TeV, and _normalization is in V/m/MHz, and _nu0 is in GHz
    	float e_theta = _normalization*((*j)/_nu0)*(_E/1000.0)/(1+pow((*j)/_nu1,1.44));
    	float deltaTheta = 2.2*(_nu0/((*j)))*PI/180.0;
    	e_theta *= exp(-0.5*(_askaryanTheta-THETA_C*PI/180.0)*(_askaryanTheta-THETA_C*PI/180.0)/(deltaTheta));
    	thetaComp->push_back(cf(0.0,-1.0*e_theta/_askaryanR)); //The minus sign is a convention.
    }
	//Electric field: r, theta, phi
	std::vector<std::vector<cf> > *result = new std::vector<std::vector<cf> >;
	result->push_back(*rComp);
	result->push_back(*thetaComp);
	result->push_back(*phiComp);
	return result;
}

std::vector<std::vector<float> >* AVZ2000::E_t(){
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
	p1 = fftw_plan_dft_1d(n,in1,out1,FFTW_CHOICE,FFTW_ESTIMATE);
	p2 = fftw_plan_dft_1d(n,in2,out2,FFTW_CHOICE,FFTW_ESTIMATE);
	p3 = fftw_plan_dft_1d(n,in3,out3,FFTW_CHOICE,FFTW_ESTIMATE);
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
	for(int i=0;i<n;++i){
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
    //to the R (2001) paper, and that the either choice of convention produces the same answer.
    if(FFTW_CHOICE==FFTW_BACKWARD){
        std::reverse(Er_t.begin(),Er_t.end());
        std::reverse(Etheta_t.begin(),Etheta_t.end());
        std::reverse(Ephi_t.begin(),Ephi_t.end());
    }
	result->push_back(Er_t);
	result->push_back(Etheta_t);
	result->push_back(Ephi_t);
	return result;
}

void AVZ2000::emShower(float E){
    _E = E;
    _isEM = 1;
    _isHAD = 0;
}

void AVZ2000::hadShower(float E){
	_E = E;
    _isHAD = 1;
    _isEM = 0;
}

void AVZ2000::setNu0(float n)
{
	_nu0 = n;
}

void AVZ2000::setNu1(float n)
{
	_nu1 = n;
}