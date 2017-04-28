#ifndef HANSONCONNOLLY_H_
#define HANSONCONNOLLY_H_
//Askaryan class
//Author: Jordan C. Hanson
//Aug 27th, 2015
//Adapted from Ralston and Buniy (2001)

#include "Askaryan.h"
#include <cmath>

#define ICE_RAD_LENGTH 36.08
#define STANDARD_ASK_DEPTH 5.0
#define STANDARD_ASK_NMAX 1000.0
#define NORM 1.0

class HansonConnolly : public Askaryan {
    public :
        //Constructor/Destructor
        HansonConnolly() :
            _isEM(1), //EM shower, use emShower()
            _isHAD(0), //HAD shower, use hadShower()
            _rho0(10.0),
            _useFormFactor(true),
            _askaryanDepthA(STANDARD_ASK_DEPTH),
            _Nmax(STANDARD_ASK_NMAX),
            _strictLowFreqLimit(false)
        {};
        ~HansonConnolly(){}; //What should we clean up?
        void toggleFormFactor(); //What it sounds like: use or don't use form factor.
        void toggleLowFreqLimit(); //What it sounds like: turn on strictLowFreqLimit.
        void setAskDepthA(float); //m
        void setNmax(float); //per 1000
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
	private:
		float _askaryanDepthA; //meters
		float _Nmax; //excess electrons over positrons, per 1000, at shower max
        int _isEM; //Electromagnetic parameterizations
        int _isHAD; //Hadronic parameterizations
        float _rho0; //Form factor parameter, with units 1/m
        //Use the _rho0 parameter above, in a single exponential model from the complex analysis paper (2017)
        bool _useFormFactor;
        //Require that even under the LPM elongation, the low-frequency radiation is the same as without LPM
        //Similar to a strict total track length requirement
        bool _strictLowFreqLimit;
};
#endif
