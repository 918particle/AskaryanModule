#ifndef HANSONCONNOLLY_H_
#define HANSONCONNOLLY_H_
//Askaryan class
//Author: Jordan C. Hanson
//Aug 27th, 2015
//Adapted from Ralston and Buniy (2001)

//Variables defined for one interaction, (one angle and distance), 
//but continuous frequency.

#include "Askaryan.h"
#include <cmath>

#define FFTW_CHOICE FFTW_BACKWARD
#define PI 3.14159
#define LIGHT_SPEED 0.3
#define COS_THETA_C 0.561798
#define THETA_C 55.82
#define INDEX 1.79
#define ICE_DENSITY 0.9167
#define ICE_RAD_LENGTH 36.08
#define STANDARD_ASK_DEPTH 5.0
#define STANDARD_ASK_R 1000.0
#define STANDARD_ASK_NMAX 1000.0
#define NORM 1.0
#define RADDEG 0.01745

class HansonConnolly : public Askaryan {
    public :
        //Constructor/Destructor
        HansonConnolly() :
            _isEM(0), //EM shower, use emShower()
            _isHAD(0), //HAD shower, use hadShower()
            _rho0(10.0),
            _useFormFactor(true),
            _askaryanDepthA(STANDARD_ASK_DEPTH),
            _askaryanR(STANDARD_ASK_R),
            _Nmax(STANDARD_ASK_NMAX),
            _askaryanTheta(THETA_C*PI/180.0),
            _strictLowFreqLimit(false)
        {};
        ~HansonConnolly(){}; //What should we clean up?
	protected:
		float _askaryanTheta; //radians
		float _askaryanR; //meters
		float _askaryanDepthA; //meters
		float _Nmax; //excess electrons over positrons, per 1000, at shower max
		float _E; //energy in GeV
        int _isEM; //Electromagnetic parameterizations
        int _isHAD; //Hadronic parameterizations
        float _rho0; //Form factor parameter, with units 1/m
        //Use the _rho0 parameter above, in a single exponential model from the complex analysis paper (2017)
        bool _useFormFactor;
        //Require that even under the LPM elongation, the low-frequency radiation is the same as without LPM
        //Similar to a strict total track length requirement
        bool _strictLowFreqLimit;
        void toggleFormFactor(); //What it sounds like: use or don't use form factor.
        void toggleLowFreqLimit(); //What it sounds like: turn on strictLowFreqLimit.
		void setAskTheta(float); //radians
		void setAskR(float); //m
		void setAskDepthA(float); //m
		void setNmax(float); //per 1000
		void setAskE(float); //GeV
        float getAskE(); //GeV
        float getAskR(); //meters
        float getAskDepthA(); //m
        float getAskNmax(); //pure number
        float getAskEta(float); //pure number
		void emShower(float); //Shower parameters from energy in GeV
		void hadShower(float); //Shower parameters from energy in GeV
        void setFormScale(float); //Set shape of shower (meters^{-1}).
		std::vector<float>* k(); //1/meters
		std::vector<float>* eta(); //unitless
		std::vector<cf>* I_ff(); //m
		std::vector<std::vector<cf> >* E_omega(); //V/m/MHz
		std::vector<std::vector<float> >* E_t(); //V/m
        void lpmEffect();
};
#endif
