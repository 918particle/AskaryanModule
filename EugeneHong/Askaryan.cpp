#include "Askaryan.h"
#include <algorithm>
#include <iostream>
#include <cmath>

std::vector<std::vector<float> >* Askaryan::showerProfile(float E_shower,int shower_mode,float shower_step_m,int param_model){
    std::vector<float> *depth = new std::vector<float>; depth->clear();
    std::vector<float> *Q_shower = new std::vector<float>; Q_shower->clear();
    std::vector<float> *LQ = new std::vector<float>; LQ->clear();

    float params[5];
    float X_0_const = 36.08;
    float X_max;
    float X_max_m;
    //Carl Pfender's fit paramters
    if(param_model==1){
        // EM shower case
        if(shower_mode==0){
            params[0] = 0.168971; // S_0
            params[1] = 37.5961; // X_0
            params[2] = 59.9807; // lambda
            params[3] = 0.158426; // E_c
            params[4] = E_shower; //Energy in GeV
            X_max = params[1]*log(params[4]/params[3]); // in g/cm2
            X_max_m = X_max/0.917/100.; // in m
        }
        // Hadronic shower case
        else if(shower_mode==1){
            params[0] = 0.1261; // S_0
            params[1] = 39.62; // X_0
            params[2] = 73.98; // lambda
            params[3] = 0.1691; // E_c
            params[4] = E_shower; //Energy in GeV
            X_max = params[1]*log(params[4]/params[3]);
            X_max_m = X_max/0.917/100.; // in m
        }
    }
    //Jaime Alvarez-Muniz's fit parameters
    else if(param_model==0){
        // EM shower case
        if (shower_mode==0){
            params[0] = 0.073; // E_c
            params[1] = E_shower; //Energy in GeV
            X_max = X_0_const*log(params[1]/params[0]); // not correct but just a approx.
            X_max_m = X_max/0.917/100.; // in m
        }
        // Hadronic shower case
        else if(shower_mode==1){
            params[0] = 0.11842; // S_0
            params[1] = 39.562; // X_0
            params[2] = 113.03; // lambda
            params[3] = 0.17006; // E_c
            params[4] = E_shower; // shower energy E_0 in GeV
            X_max = params[1]*log(params[4]/params[3]);
            X_max_m = X_max/0.917/100.; // in m
        }
    }
    int downflag=0; // after X_max
    float tempLQ=0;
    float currentN=0;
    int steps=0;
    int steps_limit=100000;
    float shower_step_gcm2=shower_step_m*1.e2*0.917; // g/cm2
    float shower_step_gcm2_X0factor=shower_step_gcm2/X_0_const; // in unit of radiation length
    float gcm2_tmp=shower_step_gcm2_X0factor; // don't start with zero
    while (downflag==0||currentN>100){
        if (shower_mode==0){ //used to have AND param_model==0 ...why? JCH Aug 28th 2015
            currentN=Greisen(gcm2_tmp,params); // input value gcm2_tmp is in unit of radiation length
        }
        else{
            currentN=GaisserHillas(gcm2_tmp,params);
        }
        if(currentN<4) currentN=0; //The 4 comes from the choice of constant 25% charge excess
        Q_shower->push_back(currentN*0.25);
        tempLQ+=currentN*0.25;
        depth->push_back(gcm2_tmp*X_0_const/0.917/100.0); // 0.917 for ice density, 100 for cm to m
        if (downflag==0&&depth->back()>X_max_m) downflag=1; // now we are going down in shower profile
        if (steps>steps_limit) break; // if steps go too long, come out from while loop
        gcm2_tmp += shower_step_gcm2_X0factor;
        steps++;
    }
    LQ->push_back(tempLQ);
    std::vector<std::vector<float> > *outputs = new std::vector<std::vector<float> >;
    outputs->push_back(*depth);
    outputs->push_back(*Q_shower);
    outputs->push_back(*LQ);
    delete depth;
    delete Q_shower;
    delete LQ;
    return outputs;
}

float Askaryan::Greisen(float x_in, float *par){
    float E_c = par[0];
    float E_0 = par[1];
    // fit parameter is in unit of radiation length
    float value =  0.31/sqrt( log(E_0/E_c) )*exp( x_in-1.5*x_in*log( (3.*x_in)/(x_in+2.*log(E_0/E_c)) ) );
    return value;
}

float Askaryan::GaisserHillas(float x_in, float *par){
    float X_max = par[1]*log(par[4]/par[3]);
    float S_0 = par[0];
    float X_0 = par[1];
    float lambda = par[2];
    float E_c = par[3];
    float E_0 = par[4];
    const float X_0_const = 36.08; // factor to change input x_in (unit of raidation) to g/cm2 unit
    float value = S_0*E_0/E_c*(X_max-lambda)/X_max*exp(X_max/lambda-1)*pow(x_in*X_0_const/(X_max-lambda),X_max/lambda)*exp(-x_in*X_0_const/lambda);
    return value;
}

int Askaryan::getLPMparameterization(){
    return whichParameterization;
}

void Askaryan::setLPMparameterization(int a){
    whichParameterization = a;
}

float Askaryan::getN(){
    return n;
}

void Askaryan::setN(float a){
    n = a;
}

std::vector<std::vector<float> >* Askaryan::GetVm_FarField_Tarray(float pnu,
                                                                  std::pair<float,float> *fracs,
                                                                  int shower_mode,
                                                                  float shower_step_m,
                                                                  int param_model,
                                                                  float viewangle,
                                                                  float atten_factor,
                                                                  int outbin){
    int skip_bins;
    std::vector<float> *Tarray = new std::vector<float>;
    std::vector<float> *Earray = new std::vector<float>;
    Tarray->clear();
    Earray->clear();
    float sin_view = sin(viewangle);
    float cos_view = cos(viewangle);
    float nice = 1.79;
    float changle_ice = acos(1.0/1.79);
    float sin_changle = sin(changle_ice);
    float offcone_factor = 1.-nice*cos_view;
    float c_ns = LIGHT_SPEED; // speed of light in m/ns
    float Const=0.0;
    float Integrate = 0.0;
    float V_s=0.0;
    float param_RA[6]={0,0,0,0,0,0};
    int shower_bin=0;
    float E_shower=0.0;
    if (shower_mode==0) {
        E_shower = pnu*fracs->first;
    }
    else {
        E_shower = pnu*fracs->second;
    }
    std::vector<std::vector<float> >* interm = this->showerProfile(E_shower,shower_mode,shower_step_m,param_model);
    std::vector<float> LQ = interm->at(2);
    std::vector<float> Q_shower = interm->at(1);
    std::vector<float> depth = interm->at(0);
    shower_bin = Q_shower.size();
    delete interm;
    
    if(shower_mode==0||shower_mode==1||shower_mode==3) { // only EM or only HAD
        //EM
        if (shower_mode==0) {
            V_s = -4.5e-14;
            param_RA[0] = 0.057;
            param_RA[1] = 2.87;
            param_RA[2] = -3.;
            param_RA[3] = -0.03;
            param_RA[4] = -3.05;
            param_RA[5] = -3.5;
            Const=sin_view/sin_changle*(1.0/LQ[0])*V_s*E_shower/1.e12;
        }
        //HAD
        else if(shower_mode==1) {
            V_s = -3.2e-14;
            param_RA[0] = 0.043;
            param_RA[1] = 2.92;
            param_RA[2] = -3.21;
            param_RA[3] = -0.065;
            param_RA[4] = -3.00;
            param_RA[5] = -2.65;
            E_shower=pnu*fracs->second;
            Const = sin_view/sin_changle*(1.0/LQ[0])*V_s*E_shower/1.e12;
        }
        
        // ok, let's just calculate near signal time bins
        float shower_dt=(shower_step_m*shower_bin)/c_ns; //shower length in time
        float test_signal_window=fabs(offcone_factor)*shower_dt*1.2+2.0; //additional 2 ns for changle_ice case
        // we also have to calculate when the window should start
        float test_signal_Tinit=offcone_factor*shower_dt/2.0-test_signal_window/2.0;
        // then we can decide the time step of the signal waveform
        float test_dT=test_signal_window/(double)outbin;
        //calculate new integrate step in z (meters) depending on offcone angle.
        //10 deg off is the maximum case and use default step in that case.
        float test_shower_step;
        if (fabs(offcone_factor)<1e-5) test_shower_step=1.0;
        else test_shower_step=5.e-4/fabs(offcone_factor);
        if (test_shower_step>1.0) test_shower_step=1.0; //maximum value is 1m step
        skip_bins = (int)(test_shower_step/shower_step_m);
        if (skip_bins<1) skip_bins=1;
        test_shower_step = skip_bins*shower_step_m;
        int new_shower_bin = (int)(shower_bin/skip_bins); //new number of bins for shower profile
        int mid_old_bin;
        for (int tbin=0; tbin<outbin; tbin++) {
            Tarray->push_back(test_signal_Tinit+(double)tbin*test_dT); // in ns
            Integrate=0.0;
            for (int bin=0; bin<new_shower_bin-2; bin++) {
                mid_old_bin = bin*skip_bins;
                float Tterm = Tarray->back()-depth[mid_old_bin]*(offcone_factor/c_ns);
                if (Q_shower[mid_old_bin]<=0) {
                    Integrate+=0.0;
                }
                else {
                    Integrate+=-1.0*(Q_shower[mid_old_bin])*Param_RE_Tterm_approx(Tterm,param_RA);
                }
            }
            Earray->push_back(Const*Integrate*skip_bins*atten_factor/float(outbin));
        }
    }
    std::vector<std::vector<float> > *outputs = new std::vector<std::vector<float> >;
    outputs->push_back(*Tarray);
    outputs->push_back(*Earray);
    delete Tarray;
    delete Earray;
    return outputs;
}

float Askaryan::Param_RE_Tterm_approx(float Tterm, float *par) {
    float value=0.0;
    if (Tterm>0.0){
        if(fabs(Tterm/par[0])<1.0e-2){
            value+=-1.0/par[0]*(1.0-Tterm/par[0]+Tterm*Tterm/(par[0]*par[0]*2.0)-Tterm*Tterm*Tterm/(par[0]*par[0]*par[0]*6.0));
        }
        else{
            value+=-1.0/par[0]*exp(-1.0*Tterm/par[0]);
        }
        if(fabs(Tterm*par[1])<1.0e-2){
            value+=par[2]*par[1]*(1.0+(par[2]-1.0)*par[1]*Tterm+(par[2]-1.0)*(par[2]-1.0-1.0)/2.0*par[1]*par[1]*Tterm*Tterm+(par[2]-1.0)*(par[2]-1.0-1.0)*(par[2]-1.0-2.0)/6.0*par[1]*par[1]*par[1]*Tterm*Tterm*Tterm);
        }
        else{
            value+=par[2]*par[1]*pow(1.0+par[1]*Tterm,par[2]-1.0);
        }
    }
    else{
        if(fabs(Tterm/par[3])<1.0e-2){
            value+=-1.0/par[3]*(1.0-Tterm/par[3]+Tterm*Tterm/(par[3]*par[3]*2.0)-Tterm*Tterm*Tterm/(par[3]*par[3]*par[3]*6.0));
        }
        else{
            value+=-1.0/par[3]*exp(-1.0*Tterm/par[3]);
        }
        if(fabs(Tterm*par[4])<1.0e-2){
            value+=par[5]*par[4]*(1.0+(par[5]-1.0)*par[4]*Tterm+(par[5]-1.0)*(par[5]-1.0-1.0)/2.0*par[4]*par[4]*Tterm*Tterm+(par[5]-1.0)*(par[5]-1.0-1.0)*(par[5]-1.0-2.0)/6.0*par[4]*par[4]*par[4]*Tterm*Tterm*Tterm);
        }
        else{
            value+=par[5]*par[4]*pow(1.0+par[4]*Tterm,par[5]-1.0);
        }
    }
    return value*1.0e9;
}