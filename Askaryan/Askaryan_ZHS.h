#ifndef ASKARYAN_ZHS_H_
#define ASKARYAN_ZHS_H_
//Askaryan class
//Author: Jordan C. Hanson
//June 19th, 2018
//Adapted from Ralston and Buniy (2001)

//Variables defined for one interaction, (one angle and distance), 
//but continuous frequency.

#include <vector>
#include <cmath>
#include <complex>
#include "Askaryan.h"

typedef std::complex<float> cf;

class Askaryan_ZHS : public Askaryan
{
	protected:
		float _askaryanTheta; //radians
		std::vector<float>* _askaryanFreq; //GHz
		float _askaryanR; //meters
		float _E; //energy in GeV
	private:
		std::string FFTW_CHOICE;
		float PI;
		float LIGHT_SPEED;
		float INDEX;
		float STANDARD_ASK_R;
		float RADDEG;
		float COS_THETA_C;
	public:
        Askaryan_ZHS(): _askaryanTheta(55.82*PI/180.0),
					_askaryanR(1000.0),
					_E(1.0e3),
					FFTW_CHOICE("FFTW_BACKWARD"),
					PI(3.14159),
					LIGHT_SPEED(0.29972),
					INDEX(1.78),
					STANDARD_ASK_R(1000.0),
					RADDEG(0.01745),
					COS_THETA_C(0.561797753){};
		void setAskTheta(float); //radians
		void setAskFreq(std::vector<float>*); //GHz
		void setAskR(float); //m
		void setAskE(float); //GeV
		float criticalF(); //GHz
		float getAskE(); //GeV
		float getAskR(); //meters
		std::vector<std::vector<cf> >* E_omega(); //V/m/MHz
		std::vector<std::vector<float> >* E_t(); //V/m
		std::vector<float>* time(); //ns
		void setIndex(float);
};
#endif
