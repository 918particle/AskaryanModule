#include "Askaryan.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>
#include <utility>
using namespace std;

int main(int argc, char **argv){
    char title[100];
    float E = atof(argv[1]);
    sprintf(title,"shower_%s.dat",argv[2]);
    ofstream out(title);
    Askaryan *h = new Askaryan();
    vector<float> *t = new vector<float>;
    t->clear();
    float tt_start = -2.5+0.1;
    float tt_stop = 2.5;
    float dt = 0.1;
    for (float tt=tt_start; tt<tt_stop; tt=tt+dt) t->push_back(tt);
    h->setAskTimes(t);
    h->standardInitialize();
    h->hadShower(E);
    float theta_start = 53.8;
    float theta_stop = 57.8;
    float dTheta = 0.025;
    for (float theta=theta_start; theta<=theta_stop; theta=theta+dTheta){
        h->setAskTheta(theta*RADDEG);
        pair<float,float> *fracs = new pair<float,float>(0.01,0.99);
        vector<float> *E_t = new vector<float>;
        E_t->clear();
        E_t = h->GetVm_FarField_Tarray(fracs,0.1);
        vector<float>::iterator i;
        for (i=E_t->begin(); i!=E_t->end(); ++i) out<<(*i)<<" ";
        out<<endl;
        delete fracs;
        delete E_t;
    }
    delete h;
    return 0;
}