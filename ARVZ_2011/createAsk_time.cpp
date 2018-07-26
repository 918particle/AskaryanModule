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
	float dt = 0.01;
	int t_min = -300;
	int t_max = 300;
	char title[100];
	Askaryan *h = new Askaryan();
	h->setAskR(1000.0); // meters
	h->setAskE(atof(argv[1])); //Specified in GeV.
	h->setAskTheta((atof(argv[2])+55.82)*3.14159/180.0);
	h->SetEmHad(true,false);
	vector<float> *times = new vector<float>;
	for(int i=t_min;i<t_max;++i)
	{
		times->push_back(i*dt);
	}
	h->setAskTimes(times);
	vector<vector<float> > *E = new vector<vector<float> >;
	E = h->E_t();
	vector<float> eTheta = E->at(1);
	delete E;
	for(int i=0;i<eTheta.size();++i)
	{
		cout<<times->at(i)<<" "<<h->getAskR()*eTheta[i]<<endl;
	}
}
