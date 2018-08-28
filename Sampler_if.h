/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sampler_if.h
 * Author: cancian
 *
 * Created on 14 de Agosto de 2018, 13:20
 */

#ifndef Sampler_IF_H
#define Sampler_IF_H

#include <vector>

/*   SAMPLER REPLACES MMC    */

/* Example of Sampler instantiation:
 Sampler_if* sampler = new Traits<Sampler_if>::Implementation();
 */

class Sampler_if {
public:
	virtual ~Sampler_if() {}  // You need this or your object will not be correctly destroyed.

	struct RNG_Parameters{
		unsigned int seed;
	};
public: // probability distributions
	virtual double random() = 0;
	virtual double sampleUniform(double min, double max) = 0;
	virtual double sampleExponential(double mean) = 0;
	virtual double sampleErlang(double mean, int M) = 0;
	virtual double sampleNormal(double mean, double stddev) = 0;
	virtual double sampleGamma(double mean, double alpha) = 0;
	virtual double sampleBeta(double alpha, double beta, double infLimit, double supLimit) = 0;
	virtual double sampleWeibull(double alpha, double scale) = 0;
	virtual double sampleLogNormal(double mean, double stddev) = 0;
	virtual double sampleTriangular(double min, double mode, double max) = 0;
	virtual double sampleDiscrete(const std::vector<double>& Prob) = 0;
public:
	virtual void setRNGparameters(RNG_Parameters param) = 0;
	virtual RNG_Parameters getRNGparameters() const = 0;
};

#endif /* Sampler_IF_H */

