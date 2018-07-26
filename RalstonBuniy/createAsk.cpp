#include "Askaryan.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>
#include <complex>
#include <cmath>
using namespace std;

int main(int argc, char **argv){
	char title[100];
	vector<float> *freqs = new vector<float>;
	float df = 1.0;
	for(float f1 = 1.0; f1<10.0; f1+=df) freqs->push_back(f1*1e-3);
	for(float f1 = 1.0; f1<10.0; f1+=df) freqs->push_back(f1*1e-2);
	for(float f1 = 1.0; f1<10.0; f1+=df) freqs->push_back(f1*1e-1);
	for(float f1 = 1.0; f1<10.0; f1+=df) freqs->push_back(f1*1e+0);
	for(float f1 = 1.0; f1<10.0; f1+=df) freqs->push_back(f1*1e+1);
	Askaryan *h = new Askaryan();
	h->setAskFreq(freqs);
	h->setAskR(1000.0); // 1km
	h->setFormScale(10.0);
	h->setAskE(atof(argv[1])); //Specified in GeV.
	h->emShower(atof(argv[1])); //Specified in GeV.
	for(float theta=0.0;theta>=-10.0;theta-=2.5)
	{
		sprintf(title,"shower_%3.1f_%3.1f_JCAC.dat",atof(argv[1]),theta);
		ofstream out(title);
		h->setAskTheta((theta+55.82)*3.14159/180.0);
		vector<vector<cf> > *Eshow = new vector<vector<cf> >;
		Eshow = h->E_omega();
		vector<cf> eTheta = Eshow->at(1);
		delete Eshow;
		//Units: R |E|/E_c (V/MHz/TeV)
		for(unsigned int j=0;j<eTheta.size();++j)
		{
			out<<freqs->at(j)<<" "<<abs(eTheta[j])*h->getAskR()/h->getAskE()*1000.0<<endl;
		}
		out.close();
	}
	delete h;
	delete freqs;
	return 0;
}
