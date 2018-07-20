#include "Askaryan.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>
#include <complex>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char **argv){
	char title[100];
	// vector<float> *freqs = new vector<float>;
	// float f_i = 0.0; //GHz
	// float f_f = 10.0; //GHz
	// float df = 0.01; //GHz
	// for(float f=f_i;f<=f_f;f+=df)
	// {
	// 	freqs->push_back(f);
	// }
	vector<float> *t = new vector<float>;
	for(int i=-500;i<500;++i)
	{
		t->push_back(i * 0.05);
	}
	Askaryan *h = new Askaryan();
	h->setAskTimes(t);
	// h->setAskFreq(freqs);
	h->setAskR(1000.0); // meters
	h->setAskE(atof(argv[1])); //Specified in GeV.
	for(float theta=0.0;theta>=-10.0;theta-=2.5)
	{
		h->setAskTheta((theta+55.82)*3.14159/180.0);
		sprintf(title,"shower_%3.1f_%3.1f_zhs_t.dat",atof(argv[1]),theta);
		ofstream out(title);
		vector<vector<float> > *Eshow = new vector<vector<float> >;
		Eshow = h->E_t();
		vector<float> eTheta = Eshow->at(1);
		//Units: V/GeV vs. time
		vector<float>::iterator j,k;
		for(j=h->time()->begin(),k=eTheta.begin();j!=h->time()->end(),k!=eTheta.end();++j,++k)
		{
			out<<(*j)<<" "<<(*k)*h->getAskR()<<endl;
		}
		out.close();
		// delete t;
		delete Eshow;
	}
	delete h;
	// delete freqs;
	return 0;
}
