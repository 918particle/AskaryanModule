#ifndef ASKARYAN_H_
#define ASKARYAN_H_
//Askaryan class
//Author: Jordan C. Hanson
//Sept 11, 2015
//Adapted from AraSim 1.0, and Eugene Hong's dissertation, and Signal.hh class.

//This is a similar class choice to EugeneHong, but specifying exact time bins rather than
//letting the code determine the time bins.  Also contains similar methods to RalstonBuniy

//The X_max parameter fit that goes into the Greisen and Gaisser-Hillas formulae:
//Carl Pfender's, from OSU.

#include <vector>
#include <cmath>
#include <utility>
#include "global.h"

class Askaryan {
protected:
    float _askaryanTheta; //viewing angle in radians
    std::vector<float>* _askaryanTimes; //ns, with retarded time of zero corresponding to on-cone peak
    float _askaryanR; //meters
    float _E; //energy in GeV
    int _shower_mode; //electromagnetic or hadronic
public:
    std::vector<std::vector<float> >* showerProfile(float,int,float);
    std::vector<float>* GetVm_FarField_Tarray(std::pair<float,float>*,float);
    float Param_RE_Tterm_approx(float,float*); //Electric field form factors from ARVZ (1D).
    float Greisen(float,float*); //Electromagnetic shower profile
    float GaisserHillas(float,float*); //Hadronic shower profile
    void emShower(float); //Energy in GeV
    void hadShower(float); //Energy in GeV
    void setAskE(float); //GeV
    void setShowerMode(int); //0 = electromagnetic, 1 = hadronic
    void setAskR(float); //m
    void standardInitialize();
    void setAskTheta(float);
    void setAskTimes(std::vector<float>*);
};
#endif