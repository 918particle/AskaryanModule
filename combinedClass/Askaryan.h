#ifndef ASKARYAN_H_
#define ASKARYAN_H_
//Askaryan class
//Author: Jordan C. Hanson
//April 20th, 2017

#include <complex>
#include <vector>

typedef std::complex<float> cf;

#define FFTW_CHOICE FFTW_BACKWARD
#define PI 3.14159
#define LIGHT_SPEED 0.3
#define COS_THETA_C 0.561798
#define THETA_C 55.82
#define INDEX 1.78
#define ICE_DENSITY 0.9167
#define STANDARD_ASK_R 1000.0
#define STANDARD_ASK_E 1.0e9
#define RADDEG 0.01745

class Askaryan
{
    public:
        //Constructor/Destructor
        Askaryan() : 
            _askaryanR(STANDARD_ASK_R),
            _askaryanTheta(THETA_C*PI/180.0),
            _E(STANDARD_ASK_E)
        {};
        virtual ~Askaryan(){};
        //Virtual functions to be defined by derived classes
        virtual std::vector<std::vector<cf> >* E_omega()=0; //V/m/MHz.
        virtual std::vector<std::vector<float> >* E_t()=0; //V/m.
        virtual void emShower(float)=0; //Argument is energy in GeV
        virtual void hadShower(float)=0; //Argument is energy in GeV
        //Setting parameters
        void setAskR(float); //m
        void setAskTheta(float); //radians
        void setAskE(float); //GeV
        void setAskFreq(std::vector<float>*); //GHz
        //Functions
        float criticalF(); //GHz
        std::vector<float>* time(); //ns
        std::vector<float>* freq(); //GHz
    protected:
        //Data
        std::vector<float>* _askaryanFreq; //GHz
        float _askaryanR; //meters
        float _askaryanTheta; //radians
        float _E; //energy in GeV
};
#endif
