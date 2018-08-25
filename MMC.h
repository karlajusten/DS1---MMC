/*
 * MMC.h
 *
 *  Created on: 15 de ago de 2018
 *      Author: karla
 */

#ifndef MMC_H_
#define MMC_H_


#include <stdint.h>

class MMC {

private:
	uint32_t rotr32(uint32_t x, unsigned r);

public:
	MMC();
	virtual ~MMC();

	struct RNG_Parameters{
		uint64_t  ling_seed;
		uint64_t multiplier;
		uint64_t increment; // an arbitrary odd constant
	};

	double random();
	double uniform(double min, double max);
	double exponential(double mean);
	double erlang(double mean, int M);
	double normal(double mean, double stddev);
	double gamma(double mean, double alpha);
	double beta(double alpha, double beta, double infLimit, double supLimit);
	double weibull(double alpha, double scale);
	double logNormal(double mean, double stddev);
	double triangular(double min, double mode, double max);
	double discrete(double value, double acumProb, ...);

	void setRNGparameters(RNG_Parameters param);
	RNG_Parameters getRNGparameters();

private:
	RNG_Parameters param;
};

#endif /* MMC_H_ */
