#include "Askaryan.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>
#include <complex>
using namespace std;

float Eq16(float,float,float);

int main(int argc, char **argv)
{
    float df_ghz = 0.02; //GHz
    float f_max = 4.0; //GHz
    float f_min = 0.0; //GHz
    float Energy = atof(argv[1]); //GeV
    int isEMShower = 1;
    int isHADShower = 0;
    int whichComponent = 1; //0 is r, 1 is theta, 2 is phi
    Askaryan *h = new Askaryan();
    vector<vector<float> > *Eshow = new vector<vector<float> >;
    vector<float> *freqs = new vector<float>;
    vector<float> e;
    vector<float> *t = new vector<float>;
    float R = 0.0;
    
    for(float i=f_min;i<f_max;i+=df_ghz) freqs->push_back(i);
    h->setAskFreq(freqs);
    h->setAskTheta((THETA_C-0.3)*PI/180.0);
    if(isEMShower) h->emShower(Energy);
    else if(isHADShower) h->hadShower(Energy);
    else return -1;
    h->setFormScale(7.5);
    h->lpmEffect();
    Eshow = h->E_t();
    e = Eshow->at(whichComponent);
    t = h->time();
    R = h->getAskR();
    ofstream out(argv[2]);
    for(int j=0;j<e.size();++j) out<<t->at(j)<<" "<<" "<<e[j]*R<<" "<<Eq16(t->at(j)-30,Energy/1000.0,1/(2.0*f_max))<<" "<<endl;
    out.close();
    
    delete h;
    delete Eshow;
    delete freqs;
	return 0;
}

float Eq16(float t,float E,float dt)
{
    float norm = 1.4e-5*E/dt; //V E is in TeV, and dt is in ns
    if(t>=0.0)
    {
        return norm*((-1.0/0.057)*exp(-t/0.057)-3*2.87*pow(1+2.87*t,-4));
    }
    else
    {
        return norm*((1.0/0.030)*exp(t/0.030)+3*3.05*pow(1-3.05*t,-4.5));
    }
}
