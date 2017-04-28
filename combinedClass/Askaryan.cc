//Askaryan.cpp

#include "Askaryan.h"
#include <fftw3.h>
#include <algorithm>

void Askaryan::setAskFreq(std::vector<float> *x){
	_askaryanFreq = x;
}

void Askaryan::setAskR(float x){
	_askaryanR = x;
}

void Askaryan::setAskTheta(float x){
	_askaryanTheta = x;
}

void Askaryan::setAskE(float x){
	_E = x;
}

float Askaryan::criticalF(){
	return *max_element(_askaryanFreq->begin(),_askaryanFreq->end());
}

std::vector<float>* Askaryan::freq(){
	return _askaryanFreq;
}

std::vector<float>* Askaryan::time(){
	float dt = 1.0/(2.0*criticalF());
	int n = 2*_askaryanFreq->size();
	std::vector<float> *result = new std::vector<float>;
	for(int i=0;i<n;++i) result->push_back(float(i)*dt);
	return result;
}
