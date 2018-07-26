#ifndef ASKARYAN_H_
#define ASKARYAN_H_
//Askaryan class
//Author: Jordan C. Hanson
//June 19th, 2018
//Adapted from Ralston and Buniy (2001)

//Variables defined for one interaction, (one angle and distance), 
//but continuous frequency.

#include <vector>
#include <cmath>
#include <complex>

typedef std::complex<float> cf;

class Askaryan
{
	public:
		virtual std::vector<std::vector<cf> >* E_omega()=0; //V/m/MHz
		virtual std::vector<std::vector<float> >* E_t()=0; //V/m
};
#endif
