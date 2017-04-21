#ifndef ASKARYAN_H_
#define ASKARYAN_H_
//Askaryan class
//Author: Jordan C. Hanson
//April 20th, 2017

#include <complex>
#include <vector>

typedef std::complex<float> cf;

class Askaryan
{
    public:
        //Constructor/Destructor
        Askaryan(){};
        virtual ~Askaryan(){};
        //Data
        std::vector<float>* _askaryanFreq; //GHz
        //Functions
        void setAskFreq(std::vector<float>*); //GHz
        float criticalF(); //GHz
        std::vector<float>* time(); //ns
        //Virtual functions to be defined by derived classes
        virtual std::vector<std::vector<cf> >* E_omega()=0; //V/m/MHz.
        virtual std::vector<std::vector<float> >* E_t()=0; //V/m.
};
#endif
