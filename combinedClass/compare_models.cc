#include <iostream>
#include <fstream>
#include "Askaryan.h"
#include "HansonConnolly.h"
#include "ZHS.h"
#include "AVZ2000.h"

std::vector<float>* CreateFrequencies(float df,float fmax)
{
	std::vector<float> *freqs = new std::vector<float>;
	for(float f1 = 0.0; f1<fmax; f1=f1+df) freqs->push_back(f1);
	return freqs;
}

HansonConnolly* SpecificSetup1()
{
    HansonConnolly *hc = new HansonConnolly();
    hc->setFormScale(1/(sqrt(2.0*3.14159)*0.05));
    hc->setAskFreq(CreateFrequencies(0.01,3.0));
    hc->toggleLowFreqLimit();
    hc->emShower(1.0e9);
    hc->setAskR(1000.0);
    hc->setAskTheta(55.8*PI/180.0);
    // hc->lpmEffect();
    return hc;
}

ZHS* SpecificSetup2()
{
    ZHS *zhs = new ZHS();
    zhs->setAskFreq(CreateFrequencies(0.01,3.0));
    zhs->emShower(1.0e9);
    zhs->setAskR(1000.0);
    zhs->setAskTheta(55.8*PI/180.0);
    return zhs;
}

AVZ2000* SpecificSetup3()
{
    AVZ2000 *avz = new AVZ2000();
    avz->setAskFreq(CreateFrequencies(0.01,3.0));
    avz->emShower(1.0e9);
    avz->setAskR(1000.0);
    avz->setAskTheta(55.8*PI/180.0);
    return avz;
}

void ReadoutModels(std::vector<Askaryan*> *h,std::vector<std::string> *out)
{
	//Reads out all spectra of all models to separate output streams.
	std::vector<Askaryan*>::iterator i;
	std::vector<std::string>::iterator j;
	for(i=h->begin(),j=out->begin();i!=h->end();++i,++j)
	{
		int n = (*i)->E_omega()->at(1).size();
		std::ofstream this_out(*j);
		for(int k=0;k<n;++k)
    	{
    		this_out<<(*i)->freq()->at(k)
    			<<" "<<abs((*i)->E_omega()->at(0).at(k))
    			<<" "<<abs((*i)->E_omega()->at(1).at(k))
    			<<" "<<abs((*i)->E_omega()->at(2).at(k))
    			<<std::endl;
    	}
    	this_out.close();
	}
	delete h;
	delete out;
}

int main()
{
	std::vector<std::string> *out = new std::vector<std::string>;
	out->push_back("shower_1.dat");
	out->push_back("shower_2.dat");
	out->push_back("shower_3.dat");
    std::vector<Askaryan*> *a = new std::vector<Askaryan*>;
    a->push_back(SpecificSetup1());
    a->push_back(SpecificSetup2());
    a->push_back(SpecificSetup3());
    ReadoutModels(a,out);
    return 0;
}
