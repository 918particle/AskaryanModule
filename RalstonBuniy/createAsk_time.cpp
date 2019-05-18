#include "Askaryan.h"
#include <cstdlib>
#include <fstream>

int main(int argc, char **argv)
{
	char title[100];
	std::vector<float> *freqs = new std::vector<float>;
	float f_i = 0.0; //GHz
	float f_f = 10.0; //GHz
	float df = 0.08; //GHz
	for(float f=f_i;f<=f_f;f+=df)
	{
		freqs->push_back(f);
	}
	Askaryan *h = new Askaryan();
	h->setAskFreq(freqs);
	h->setAskR(1000.0); // meters 
	h->setFormScale(10.0); //inverse meters
	h->setAskE(atof(argv[1])); //Specified in GeV
	h->hadShower(atof(argv[1])); //Specified in GeV.
	// h->lpmEffect();
	std::vector<float> t = h->time();
	for(float theta=3.0;theta>=-3.0;theta-=0.1)
	{
		h->setAskTheta((theta+55.82)*3.14159/180.0);
		sprintf(title,"shower_%3.1f_%3.1f_JCAC_t.dat",atof(argv[1]),theta);
		std::ofstream out(title);
		std::vector<std::vector<float> > Eshow = h->E_t();
		std::vector<float> eTheta = Eshow.at(1);
		//Units: V/GeV vs. time
		std::vector<float>::iterator j,k;
		// for(j=t.begin(),k=eTheta.begin();j!=t.end(),k!=eTheta.end();++j,++k)
		// {
		// 	out<<(*j)<<" "<<(*k)<<std::endl;
		// }
		out.close();
	}
	delete freqs;
	delete h;
	return 0;
}
