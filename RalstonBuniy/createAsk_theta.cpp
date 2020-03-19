#include "Askaryan.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>
#include <complex>
#include <cmath>
using namespace std;

int main(int argc, char **argv)
{
	char title[100];
	vector<float> *freqs = new vector<float>;
	freqs->push_back(atof(argv[1]));
	Askaryan *h = new Askaryan();
	h->setAskFreq(freqs);
	h->setAskR(1000.0); // 1km
	h->setFormScale(1000.0);
	h->setAskE(atof(argv[2])); //Specified in GeV.
	h->emShower(atof(argv[2])); //Specified in GeV.
	h->setAskDepthA(h->getAskDepthA()/2.0);
	h->lpmEffect();
	sprintf(title,"shower_%3.1f_JCAC_noLPM.dat",atof(argv[2]));
	ofstream out(title);
	for(float theta=30.0;theta<=80.0;theta+=0.1)
	{
		h->setAskTheta(theta*3.14159/180.0);
		vector<vector<cf> > Eshow;;
		Eshow = h->E_omega();
		vector<cf> eTheta = Eshow.at(1);
		//Units: R |E|/E_c (V/MHz/TeV)
		out<<theta<<" "<<2.0*abs(eTheta[0])*h->getAskR()/h->getAskE()*1000.0<<endl;
	}
	out.close();
	delete h;
	delete freqs;
	return 0;
}
