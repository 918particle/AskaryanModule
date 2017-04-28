//Askaryan.cpp

#include "Askaryan.h"
#include "ZHS.h"
#include <fftw3.h>
#include <algorithm>
#include <iostream>

std::vector<std::vector<cf> >* ZHS::E_omega(){
    std::vector<cf> *rComp = new std::vector<cf>;
	std::vector<cf> *thetaComp = new std::vector<cf>;
	std::vector<cf> *phiComp = new std::vector<cf>;
	std::vector<float>::iterator j;
    for(j=_askaryanFreq->begin();j!=_askaryanFreq->end();++j)
        result->push_back(2.0*PI*(*j)/(LIGHT_SPEED/INDEX));
	//Electric field: r, theta, phi
	std::vector<std::vector<cf> > *result = new std::vector<std::vector<cf> >;
	result->push_back(*rComp);
	result->push_back(*thetaComp);
	result->push_back(*phiComp);
	return result;
}

std::vector<std::vector<float> >* ZHS::E_t(){
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
    //to the RB paper, and that the either choice of convention produces the same answer.
    
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

void ZHS::emShower(float E){
    _E = E;
    _isEM = 1;
    float E_CRIT = 0.073; //GeV
	//Greissen EM shower profile from Energy E in GeV.
	std::vector<float> *nx = new std::vector<float>;
	float max_x = 50.0; //maximum number of radiation lengths
	float dx = 0.01; //small enough bin in depth for our purposes.
	float x_start = dx; //starting radiation length
	for(float x=x_start;x<max_x;x+=dx){
        float a = 0.31/sqrt(log(E/E_CRIT));
        float b = x;
        float c = 1.5*x;
        float d = log((3*x)/(x+2*log(E/E_CRIT)));
		nx->push_back(a*exp(b-c*d));
	}
    //find location of maximum, and charge excess from Fig. 5.9, compare in cm not m.
    std::vector<float>::iterator n_max = max_element(nx->begin(),nx->end());
    float excess=0.09+dx*(std::distance(nx->begin(),n_max))*ICE_RAD_LENGTH/ICE_DENSITY*1.0e-4;
	_Nmax = excess*(*n_max)/1000.0;
	//find depth, which is really the FWHM of this Greissen formula.
	std::vector<float>::iterator i;
	for(i=nx->begin();i!=nx->end();++i){
		if((*i)/(*n_max)>0.606531) break;
	}
	std::vector<float>::iterator j;
	for(j=nx->end();j!=nx->begin();--j){
		if((*j)/(*n_max)>0.606531) break;
	}
	_askaryanDepthA = dx*std::distance(i,j)/ICE_DENSITY*ICE_RAD_LENGTH/100.0; //meters
}

void ZHS::hadShower(float E){
	_E = E;
    _isHAD = 1;
    //Gaisser-Hillas hadronic shower parameterization
    std::vector<float> *nx = new std::vector<float>;
    float max_x = 2000.0; //maximum depth in g/cm^2
	float dx = 1.0; //small enough bin in depth for our purposes.
	float x_start = dx; //depth in g/cm^2
    float S0 = 0.11842;
    float X0 = 39.562; //g/cm^2
    float lambda = 113.03; //g/cm^2
    float Ec = 0.17006; //GeV
    float Xmax = X0*log(E/Ec);
	for(float x=x_start;x<max_x;x+=dx){
		float a = S0*E/Ec*(Xmax-lambda)/Xmax*exp(Xmax/lambda-1);
		float b = pow(x/(Xmax-lambda),Xmax/lambda);
		float c = exp(-x/lambda);
		nx->push_back(a*b*c);
	}
    //find location of maximum, and charge excess from Fig. 5.9, compare in cm not m.
    std::vector<float>::iterator n_max = max_element(nx->begin(),nx->end());
    float excess=0.09+dx*(std::distance(nx->begin(),n_max))/ICE_DENSITY*1.0e-4;
	_Nmax = excess*(*n_max)/1000.0;
	//find depth, which is really the FWHM of this Gaisser-Hillas 
	//formula.  I chose the 1-sigma width to better represent the gaussian.
	std::vector<float>::iterator i;
	for(i=nx->begin();i!=nx->end();++i){
		if((*i)/(*n_max)>0.606531) break;
	}
	std::vector<float>::iterator j;
	for(j=nx->end();j!=nx->begin();--j){
		if((*j)/(*n_max)>0.606531) break;
	}
	_askaryanDepthA = dx*std::distance(i,j)/ICE_DENSITY/100.0; //meters
}
