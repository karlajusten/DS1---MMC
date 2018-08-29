/*
 * MMC.h
 *
 *  Created on: 15 de ago de 2018
 *      Author: karla
 *      Author: bruno
 */

#ifndef MMC_H_
#define MMC_H_

#include <stdint.h>
#include <iostream>
#define _USE_MATH_DEFINES	
#include <cmath>
//discrete
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <tuple>
#include <vector>

class MMC {
protected:
    MMC *mmc;

public:
	MMC();
	MMC(const MMC& mmc_);
	virtual ~MMC();
	
	struct RNG_Parameters{
		uint64_t  seed;
		uint64_t multiplier;
		uint64_t increment; // Select a sequence in the 2^63 range. must be odd!
	};

	double random();
	double sampleUniform(double min, double max);
	double sampleExponential(double mean);
	double sampleErlang(double mean, int M);
	double sampleNormal(double mean, double stddev);
	double sampleGamma(double mean, double alpha);
	double sampleBeta(double alpha, double beta, double infLimit, double supLimit);
	double sampleWeibull(double alpha, double scale);
	double sampleLogNormal(double mean, double stddev);
	double sampleTriangular(double min, double mode, double max);
	double sampleDiscrete(const std::vector<double>& Prob );  //TODO args

	void setRNGparameters(RNG_Parameters param);
	RNG_Parameters getRNGparameters();

private:
	uint32_t rotr32(uint32_t x, unsigned r);
	RNG_Parameters param;
};

#endif /* MMC_H_ */
