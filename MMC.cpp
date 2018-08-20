/*
 * MMC.cpp
 *
 *  Created on: 15 de ago de 2018
 *      Author: karla
 */

#include "MMC.h"
#include <stdint.h>

MMC::MMC() {
	// TODO Auto-generated constructor stub

}

MMC::~MMC() {
	// TODO Auto-generated destructor stub
}

/*
 * Método de geração de número randômico utilizado: PCG-XSH-RR
 */
double  MMC::random(){

	//static uint64_t       seed      = 0x4d595df4d0f33173;		// Or something seed-dependent
	static uint64_t const multiplier = 6364136223846793005u;
	static uint64_t const increment  = 1442695040888963407u;	// Or an arbitrary odd constant

	uint64_t x = getRNGparameters().ling_seed;
	unsigned count = (unsigned)(x >> 59);		// 59 = 64 - 5
	RNG_Parameters new_seed;
	new_seed.ling_seed = x * multiplier + increment;
	setRNGparameters(new_seed);
	x ^= x >> 18;								// 18 = (64 - 27)/2;  ^: XOR Exclusivo

	return rotr32((uint32_t)(x >> 27), count);	// 27 = 32 - 5
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

