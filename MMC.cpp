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
    uint32_t x = random();
    uint64_t m = uint64_t(x) * uint64_t(max - min);
    return  m  >> 32;
//min * (1 - x) + max * x;
}    



double MMC::exponential(double mean){
	if( mean == 0 ) {
		throw "Division by zero condition at exponential distribution method!";
	}
	double x = random();
	//double term = (double)(-(x/mean));
	//std::cout << term << std::endl;
	return (1/mean)*exp((double)(-(x/mean)));
	//return -mean*log1p(-x);
}

double MMC::normal(double mean, double stddev){
	if( stddev == 0 ) {
		throw "Division by zero condition at normal distribution method!";
	}
	double num = (random()-mean);
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

double MMC::beta(double alpha, double beta, double infLimit, double supLimit){
	double term = (tgamma(alpha)*tgamma(beta));
	if( term == 0 ) {
		throw "Division by zero condition at beta distribution method!";
	}
	double x = random(); //PRECISA DE ALEATÓRIO UNIFORME!!!
	return (tgamma(alpha+beta)/term)*pow(x, alpha-1)*pow(1-x, beta-1);
}

double MMC::logNormal(double mean, double stddev){
	double x = random();
	if( stddev == 0 || x == 0) {
		throw "Division by zero condition at logNormal distribution method!";
	}
	double num = log(x)-mean;
	return (1/(x*stddev*sqrt(2*M_PI)))*exp((double)-(num*num)/(2*stddev*stddev));
}

