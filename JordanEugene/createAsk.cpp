#include "Askaryan.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>
#include <complex>
#include <cmath>

int main(int argc, char **argv)
{
	float t_i = -100.0;
	float delta_t = 0.5;
	float t_f = 100.0;
	Askaryan *h = new Askaryan();
	h->setAskR(1000.0);
	h->setAskE(atof(argv[1])); //Specified in GeV.
	h->setAskTheta(58*3.14/180.0);
	std::vector<float>* ti = new std::vector<float>;
	for(float t=t_i;t<=t_f;t+=delta_t) ti->push_back(t);
	h->setAskTimes(ti);
	std::pair<float,float> *f = new std::pair<float,float>;
	f->first = 1.0;
	f->second = 0.0;
	std::vector<float>* E = h->GetVm_FarField_Tarray(f,1.0);
	std::vector<float>::iterator i,j;
	for(i=ti->begin(),j=E->begin();i!=ti->end(),j!=E->end();++i,++j)
	{
		std::cout<<(*i)<<" "<<(*j)<<std::endl;
	}
	return 0;
}