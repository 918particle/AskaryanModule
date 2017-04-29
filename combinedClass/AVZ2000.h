#ifndef AVZ2000_H_
#define AVZ2000_H_
//Askaryan class
//Author: Jordan C. Hanson
//April 28th, 2017
//Adapted from Zas, Halzen, and Stanev (1991)

#include "Askaryan.h"
#include <cmath>

class AVZ2000 : public Askaryan {
    public :
        //Constructor/Destructor
        AVZ2000() :
            _isEM(1), //EM shower, use emShower()
            _isHAD(0), //HAD shower, use hadShower()
            _nu0(1.15), //nu0 parameter in AVZ (2000)
            _nu1(1.15), //nu0 parameter in AVZ (2000)
            _normalization(2.53e-7)

        {};
        ~AVZ2000(){}; //What should we clean up?
        void emShower(float); //Shower parameters from energy in GeV
        void hadShower(float); //Shower parameters from energy in GeV
        std::vector<std::vector<cf> >* E_omega(); //V/m/MHz
        std::vector<std::vector<float> >* E_t(); //V/m
        void setNu0(float);
        void setNu1(float);
	private:
        int _isEM; //Electromagnetic parameterizations
        int _isHAD; //Hadronic parameterizations
        float _nu0; //The nu_{0} parameter in AVZ (2000), in the denominator of (nu/nu_0)
        float _nu1; //THe nu_{1} parameter in AVZ (2000), in the form factor.  These numbers were different in Miocinovic et al (2006)
        float _normalization; //2.53e-7 V/m/MHz
};
#endif
