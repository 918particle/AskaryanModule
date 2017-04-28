#ifndef ZHS_H_
#define ZHS_H_
//Askaryan class
//Author: Jordan C. Hanson
//April 28th, 2017
//Adapted from Zas, Halzen, and Stanev (1991)

#include "Askaryan.h"
#include <cmath>

class ZHS : public Askaryan {
    public :
        //Constructor/Destructor
        ZHS() :
            _isEM(1), //EM shower, use emShower()
            _isHAD(0), //HAD shower, use hadShower()
        {};
        ~ZHS(){}; //What should we clean up?
        void emShower(float); //Shower parameters from energy in GeV
        void hadShower(float); //Shower parameters from energy in GeV
        std::vector<std::vector<cf> >* E_omega(); //V/m/MHz
        std::vector<std::vector<float> >* E_t(); //V/m
	private:
        int _isEM; //Electromagnetic parameterizations
        int _isHAD; //Hadronic parameterizations
};
#endif
