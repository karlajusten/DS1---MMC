/*
 * MMC.cpp
 *
 *  Created on: 15 de ago de 2018
 *      Author: karla
 *      Author: bruno
 */

#include "MMC.h"
#include <stdint.h>
#include <math.h>
#include <iostream>

MMC::MMC() {
	RNG_Parameters defaul;
	defaul.ling_seed = 0x4d595df4d0f33173;
	defaul.multiplier = 6364136223846793005u;
	defaul.increment = 1442695040888963407u;
	setRNGparameters(defaul);
}

MMC::~MMC() {
	// TODO Auto-generated destructor stub
}

/*
 * Método de geração de número randômico utilizado: PCG-XSH-RR
 */
double  MMC::random(){

	uint64_t x = getRNGparameters().ling_seed;
	unsigned count = (unsigned)(x >> 59);
	RNG_Parameters new_seed = getRNGparameters();
	new_seed.ling_seed = x * getRNGparameters().multiplier + getRNGparameters().increment;
	setRNGparameters(new_seed);
	x ^= x >> 18;								 // ^: XOR Exclusivo

	return rotr32((uint32_t)(x >> 27), count);
  //64bit pack int64_t x = (pcg32() << 32) | pcg32();

}

uint32_t MMC::rotr32(uint32_t x, unsigned r)
{
	return x >> r | x << (-r & 31);
}

void  MMC::setRNGparameters(RNG_Parameters param){
	this->param = param;
}

MMC::RNG_Parameters  MMC::getRNGparameters(){
	return this->param;
}

double MMC::uniform(double min, double max){
	    uint64_t x = random();
	     if (max == 1.0 && min == 0.0)
	     	return ldexp(x, -32);  // pcg generate floats[0,1] nearest multiple of 1/2^32 
	    uint64_t m =  x * double(max - min); 
	    return (double) (m  >> 32) + min;    
}    

double MMC::exponential(double mean){
	if( mean == 0 ) {
		throw "Division by zero condition at exponential distribution method!";
	}
	double x = random();
	return (1/mean)*exp((double)(-(x/mean)));
}

double MMC::normal(double mean, double stddev){
	if( stddev == 0 ) {
		throw "Division by zero condition at normal distribution method!";
	}
	double x = random();
	double num = (x-mean);
	//std::cout << "num = "<< num << std::endl;
	//std::cout << "secondTerm = " << exp((double)-(num*num)/(2*stddev*stddev)) << std::endl;
	//std::cout << "firstTerm = " << (1/(stddev*sqrt(2*M_PI))) << std::endl;
	return (1/(stddev*sqrt(2*M_PI)))*exp((double)-(num*num)/(2*stddev*stddev));
}

double MMC::gamma(double mean, double alpha){

	double term = (tgamma(alpha)*pow(mean, alpha));
	//std::cout << "term = "<< term << std::endl;
	if( term == 0 || mean==0) {
		throw "Division by zero condition at gamma distribution method!";
	}
	double x = random();
	//std::cout << "x = "<< random() << std::endl;
	//std::cout << "pow(x, alpha-1) = "<< pow(x, alpha-1) << std::endl;
	return 1/term * pow(x, alpha-1) * exp(-x/mean);
}
double MMC::erlang(double mean, int M){
	return gamma(mean, M);  //Erlang is gamma where alpha is an integer; by Boost and GSL 
}

double MMC::beta(double alpha, double beta, double infLimit, double supLimit){
	double term = (tgamma(alpha)*tgamma(beta));
	if( term == 0 ) {
		throw "Division by zero condition at beta distribution method!";
	}
	double x = uniform(0.0, 1.0); //PRECISA DE ALEATÓRIO UNIFORME!!!
	return (tgamma(alpha+beta)/term)*pow(x, alpha-1)*pow(1-x, beta-1);
}

double MMC::weibull(double alpha, double scale){
  double x = random();
  double m = pow (-log (x), 1 / scale);

  return alpha * m;
}

double MMC::logNormal(double mean, double stddev){
	double x = random();
	if( stddev == 0 || x == 0) {
		throw "Division by zero condition at logNormal distribution method!";
	}
	double num = log(x)-mean;
	return (1/(x*stddev*sqrt(2*M_PI)))*exp((double)-(num*num)/(2*stddev*stddev));
}

double MMC::triangular(double min, double mode, double max){
	double w =  min - mode;
	double z =  max - mode;
	double r =  max - min;
	double x = random();
	if (x < (w/r))
		return min+sqrt(w*r*x);
	else
		return max-sqrt(z*r*(1.0 - x)); 
}



