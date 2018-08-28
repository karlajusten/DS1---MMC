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
#include "Sampler_if.h"
#include <iostream>
#define _USE_MATH_DEFINES	
#include <cmath>
//discrete
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <tuple>
#include <vector>

class MMC : public Sampler_if {
protected:
    MMC *mmc;

private:
	uint32_t rotr32(uint32_t x, unsigned r);
	PCG_Parameters param;

public:
	MMC();
	MMC(const MMC& mmc_);
	virtual ~MMC();
	
	struct PCG_Parameters : public RNG_Parameters{
		uint64_t  ling_seed;
		uint64_t multiplier;
		uint64_t increment; // Select a sequence in the 2^63 range. must be odd!
	};

	double random() override;
	double sampleUniform(double min, double max) override;
	double sampleExponential(double mean) override;
	double sampleErlang(double mean, int M) override;
	double sampleNormal(double mean, double stddev) override;
	double sampleGamma(double mean, double alpha) override;
	double sampleBeta(double alpha, double beta, double infLimit, double supLimit) override;
	double sampleWeibull(double alpha, double scale) override;
	double sampleLogNormal(double mean, double stddev) override;
	double sampleTriangular(double min, double mode, double max) override;
	double sampleDiscrete(const std::vector<double>& Prob ) override;  //TODO args

	void setRNGparameters(RNG_Parameters param) override;
	RNG_Parameters getRNGparameters();

};

#endif /* MMC_H_ */
