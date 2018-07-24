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
	Askaryan *h = new Askaryan();
	h->setAskR(1000.0); // meters
	h->setAskE(atof(argv[1])); //Specified in GeV.
	h->setAskTheta((-7.1+55.82)*3.14159/180.0);
	h->SetEmHad(false,true);
	for(int i=-200;i<200;++i)
	{
		float t = i*0.01;
		cout<<t<<" "<<h->getAskR()*abs(h->A_t(t))*100.0<<endl;
	}
}
