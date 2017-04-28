#include <iostream>
#include <fstream>
#include "Askaryan.h"
#include "HansonConnolly.h"
#include "ZHS.h"
using namespace std;

vector<float>* CreateFrequencies(float df,float fmax)
{
	vector<float> *freqs = new vector<float>;
	for(float f1 = 0.0; f1<fmax; f1=f1+df) freqs->push_back(f1);
	return freqs;
}

HansonConnolly* SpecificSetup1()
{
    HansonConnolly *hc = new HansonConnolly();
    hc->setFormScale(1/(sqrt(2.0*3.14159)*0.05));
    hc->setAskFreq(CreateFrequencies(0.01,3.0));
    hc->emShower(1.0e9);
    // hc->setAskDepthA(1.5);
    hc->setAskR(1000.0);
    hc->setAskTheta(55.8*PI/180.0);
    // hc->lpmEffect();
    hc->toggleLowFreqLimit();
    return hc;
}

ZHS* SpecificSetup2()
{
    ZHS *z = new ZHS();
    z->setAskFreq(CreateFrequencies(0.01,3.0));
    z->emShower(1.0e9);
    z->setAskR(1000.0);
    z->setAskTheta(55.8*PI/180.0);
    return z;
}

void ReadoutModel(Askaryan* h,ofstream out)
{

}

int main(int argc, char **argv)
{
	char title1[100];
	char title2[100];
	char title3[100];
	char title4[100];
    sprintf(title1,"shower_%s.dat",argv[1]);
    ofstream out1(title1);
    sprintf(title2,"shower_%s.dat",argv[2]);
    ofstream out2(title2);
    sprintf(title3,"shower_%s.dat",argv[3]);
    ofstream out3(title3);
    sprintf(title4,"shower_%s.dat",argv[4]);
    ofstream out4(title4);
    vector<cf> eTheta;
    vector<float> eTheta_t;
    Askaryan *a;

	//One model
	a = SpecificSetup1();
    eTheta = a->E_omega()->at(1);
    eTheta_t = a->E_t()->at(1);
    for(int j=0;j<eTheta.size();++j)
    {
    	out1<<a->freq()->at(j)<<" "<<abs(eTheta[j])<<endl;
    }
    for(int j=0;j<eTheta_t.size();++j)
    {
    	out2<<a->time()->at(j)<<" "<<eTheta_t[j]<<endl;
    }
    //A second model
    a = SpecificSetup2();
    eTheta = a->E_omega()->at(1);
    eTheta_t = a->E_t()->at(1);
    for(int j=0;j<eTheta.size();++j)
    {
    	out3<<a->freq()->at(j)<<" "<<abs(eTheta[j])<<endl;
    }
    for(int j=0;j<eTheta_t.size();++j)
    {
    	out4<<a->time()->at(j)<<" "<<eTheta_t[j]<<endl;
    }
    out1.close();
    out2.close();
    out3.close();
    out4.close();
    return 0;
}
