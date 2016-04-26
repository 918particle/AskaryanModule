#ifndef ASKARYAN_H_
#define ASKARYAN_H_
//Askaryan class
//Author: Jordan C. Hanson
//Aug 27th, 2015
//Adapted from AraSim 1.0, and Eugene Hong's dissertation, and Signal.hh class.

//Variables defined for one interaction, (one angle and distance),
//but continuous frequency.

#include <vector>
#include <cmath>
#include <utility>
#include "global.h"

class Askaryan {
protected:
    int whichParameterization; //Determines LPM parameterization
    float n; //index of refraction
    float cAngle; //Cerenkov angle
public:
    std::vector<std::vector<float> >* showerProfile(float,int,float,int);
    std::pair<float,float>* spread(float,float,float,float);
    std::vector<std::vector<float> >* GetVm_FarField_Tarray(float,std::pair<float,float>*,int,float,int,float,float,int);
    float Param_RE_Tterm_approx(float,float*);
    float Greisen(float,float*);
    float GaisserHillas(float,float*);
    int getLPMparameterization();
    void setLPMparameterization(int);
    float getN(); //Index of refraction at the interaction depth
    void setN(float); //Set index at interaction depth
};
#endif