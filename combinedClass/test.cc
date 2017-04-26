#include <iostream>
#include <fstream>
#include "Askaryan.h"
#include "HansonConnolly.h"
using namespace std;

vector<float>* CreateFrequencies(float df)
{
	vector<float> *freqs = new vector<float>;
	for(float f1 = 1.0; f1<10.0; f1=f1+df) freqs->push_back(f1*1e-3);
	for(float f1 = 1.0; f1<10.0; f1=f1+df) freqs->push_back(f1*1e-2);
	for(float f1 = 1.0; f1<10.0; f1=f1+df) freqs->push_back(f1*1e-1);
	for(float f1 = 1.0; f1<10.0; f1=f1+df) freqs->push_back(f1*1e+0);
	for(float f1 = 1.0; f1<10.0; f1=f1+df) freqs->push_back(f1*1e+1);
	return freqs;
}

HansonConnolly* SpecificSetup()
{
    HansonConnolly *hc = new HansonConnolly();
    hc->setFormScale(1/(sqrt(2.0*3.14159)*0.03));
    hc->setAskFreq(CreateFrequencies(0.75));
    hc->emShower(1.0e9);
    hc->setAskDepthA(1.5);
    hc->setAskR(1000.0);
    hc->setAskTheta(57.0*PI/180.0);
    hc->lpmEffect();
    hc->toggleLowFreqLimit();
    return hc;
}

int main(int argc, char **argv)
{
    char title[100];
    sprintf(title,"shower_%s.dat",argv[1]);
    ofstream out(title);
    Askaryan *a = SpecificSetup();
    vector<vector<cf> > *Eshow = new vector<vector<cf> >;
    Eshow = a->E_omega();
    vector<cf> eTheta = Eshow->at(1);
    delete Eshow;
    for(int j=0;j<eTheta.size();++j) out<<abs(eTheta[j])<<endl;
    out.close();
    return 0;
}
