#include "Askaryan.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>
#include <complex>
using namespace std;

int main(){
    float df = 10.0; //MHz
    float df_ghz = df/1000.0; //GHz
    vector<float> *freqs = new vector<float>;
    for(float i=0.0;i<10.0;i+=df_ghz) freqs->push_back(i);
    Askaryan *h = new Askaryan();
    h->setAskFreq(freqs);
    h->standardInitialize();
    h->emShower(1.0e9);
    vector<vector<float> > *Eshow = new vector<vector<float> >;
    Eshow = h->E_t();
    vector<float> eTheta = Eshow->at(1);
    ofstream out("noLPM_Etheta.dat");
    for(int j=0;j<eTheta.size();++j) out<<" "<<eTheta[j]<<" "<<endl;
    out.close();
    h->lpmEffect();
    Eshow = h->E_t();
    eTheta = Eshow->at(1);
    ofstream out1("LPM_Etheta.dat");
    for(int j=0;j<eTheta.size();++j) out1<<" "<<eTheta[j]<<" "<<endl;
    out1.close();
    delete h;
    delete Eshow;
	return 0;
}
