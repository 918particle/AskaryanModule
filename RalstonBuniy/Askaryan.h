#ifndef ASKARYAN_H_
#define ASKARYAN_H_
//Askaryan class
//Author: Jordan C. Hanson
//Aug 27th, 2015
//Adapted from Ralston and Buniy (2001)

//Variables defined for one interaction, (one angle and distance), 
//but continuous frequency.

#include <vector>
#include <cmath>
#include <complex>
#include "global.h"

typedef std::complex<float> cf;

int factorial(int);
int dfactorial(int);

class Askaryan {
	protected:
		float _askaryanTheta; //radians
		std::vector<float>* _askaryanFreq; //GHz
		float _askaryanR; //meters
		float _askaryanDepthA; //meters
		float _Nmax; //excess electrons over positrons, per 1000, at shower max
		float _E; //energy in GeV
        int _isEM; //Electromagnetic parameterizations
        int _isHAD; //Hadronic parameterizations
        float _rho0; //Form factor parameter, with units 1/m
        bool _useFormFactor; //Assume a gaussian form factor in z and rho (phi symmetry).
	public:
        Askaryan(): _isEM(0), //EM shower, use emShower()
                    _isHAD(0), //HAD shower, use hadShower()
                    _rho0(10.0),
                    _useFormFactor(true) {}; //Apply form factor{};
        void toggleFormFactor(); //What it sounds like: use or don't use form factor.
		void setAskTheta(float); //radians
		void setAskFreq(std::vector<float>*); //GHz
		void setAskR(float); //m
		void setAskDepthA(float); //m
		void setNmax(float); //per 1000
		void setAskE(float); //GeV
		float criticalF(); //GHz
        float getAskE(); //GeV
        float getAskDepthA(); //m
		void standardInitialize();
		void emShower(float); //Shower parameters from energy in GeV
		void hadShower(float); //Shower parameters from energy in GeV
        void setFormScale(float); //Set shape of shower (meters).
		std::vector<float>* k(); //1/meters
		std::vector<float>* eta(); //unitless
		std::vector<cf>* I_ff(); //m
		std::vector<std::vector<cf> >* E_omega(); //V/m/MHz
		std::vector<std::vector<float> >* E_t(); //V/m
		std::vector<float>* time(); //ns
        void lpmEffect();
};
#endif
