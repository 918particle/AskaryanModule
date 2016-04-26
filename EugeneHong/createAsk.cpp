#include "Askaryan.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>
#include <utility>
using namespace std;

int main(int argc, char **argv){
    //Shower properties, energy, energy fractions.
    pair<float,float> *fracs = new pair<float,float>(0.99,0.01);
    Askaryan *h = new Askaryan();
    char title[100];
    float E = atof(argv[1]);
    sprintf(title,"shower_%s.dat",argv[2]);
    ofstream out(title);
    //Angles and times.
    float theta_start = 45.8;
    float theta_end = 65.8;
    float dtheta = 0.1;
    for (float theta=theta_start; theta<=theta_end; theta=theta+dtheta) {
        vector<vector<float> > *Eshow = new vector<vector<float> >;
        //for energy: the function takes it as GeV
        Eshow = h->GetVm_FarField_Tarray(E,fracs,0,0.1,1,theta*RADDEG,1.0,128);
        vector<float> times = Eshow->at(0);
        vector<float> eTheta = Eshow->at(1);
        delete Eshow;
        //Critical frequency first, then data.
        out<<1.0/(2.0*(times[1]-times[0]))<<" "; //GHz
        for(int j=0;j<eTheta.size();++j) out<<" "<<eTheta[j]<<" ";
        out<<endl;
    }
    out.close();
    delete h;
    return 0;
}