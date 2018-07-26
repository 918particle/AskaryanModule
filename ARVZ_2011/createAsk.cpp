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
	vector<float> *t = new vector<float>;
	float dt = 0.2; //ns
	int t_min = -600;
	int t_max = 600;
	for(int i=t_min;i<t_max;++i)
	{
		t->push_back(i*dt);
	}
	float fc = 0.5/dt;
	float df = 1.0/(t->size()*dt);
	vector<float> *freqs = new vector<float>;
	for(float f=0;f<fc;f+=df)
	{
		freqs->push_back(f);
	}
	Askaryan *h = new Askaryan();
	h->setAskTimes(t);
	h->setAskFreq(freqs);
	h->SetEmHad(true,false);
	h->setAskR(1000.0); // 1km
	h->setAskE(atof(argv[1])); //Specified in GeV.
	for(float theta=0.0;theta>=-10.0;theta-=2.5)
	{
		sprintf(title,"shower_%3.1f_%3.1f_ARVZ.dat",atof(argv[1]),theta);
		ofstream out(title);
		h->setAskTheta((theta+55.82)*3.14159/180.0);
		vector<vector<cf> > *Eshow = new vector<vector<cf> >;
		Eshow = h->E_omega();
		vector<cf> eTheta = Eshow->at(1);
		delete Eshow;
		//Units: R |E|/E_c (V/MHz/TeV)
		for(unsigned int j=1;j<h->getAskFreq()->size()-1;++j)
		{
			out<<h->getAskFreq()->at(j)<<" "<<abs(eTheta[j])*h->getAskR()/h->getAskE()*1000.0<<endl;
		}
		out.close();
	}
	delete h;
	delete freqs;
	delete t;
	return 0;
}