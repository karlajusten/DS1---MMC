/*
 * Test.cpp
 *
 *  Created on: 26 de ago de 2018
 *      Author: karla
 */

#include <iostream>
#include <stdio.h>
#include "Test.h"
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <random>
#include <tuple>
#include <vector>

using std::cout;
using std::endl;


#define buffer_size 512
#define nrolls 10000  // number of experiments
#define nstars 100    // maximum number of stars to distribute

Test::Test() {
}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

void Test::random(){
	uint32_t buffer[buffer_size];

	while (1) {

		for (int k = 0; k < buffer_size; k++)
			buffer[k] = mmc->random();
		fwrite((void *)buffer, sizeof(buffer), 1, stdout);

	}
}

void Test::uniform(){
double min = 0;
double max = 10; 
std::cout << "uniform_distribution " << min << " - " << max << ":" << std::endl;
   int p[10]={};

   for (int i=0; i<nrolls; ++i) {
		double number = mmc->sampleUniform(min, max);
		if ((number>=min)&&(number<max)) ++p[int(number)];
	}

   for (int i=0; i<10; ++i) {
	 std::cout << i << "-" << (i+1) << ": ";
	 std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
   }
}

void Test::exponencial(){
	const int nintervals=10; // number of intervals

	double generator = 3.5 ;

	int p[nintervals]={};

	/*for (int i=0; i<50; ++i) {
		double number = mmc->exponential(generator);
		std::cout << number << std::endl;
	}*/

	for (int i=0; i<nrolls; ++i) {
	    long double number = mmc->sampleExponential(generator);
	    if(number>=0.9)
	    	p[9]++;
	    else if(number>=0.8)
	    	p[8]++;
	    else if(number>=0.7)
	    	p[7]++;
	    else if(number>=0.6)
	    	p[6]++;
	    else if(number>=0.5)
	    	p[5]++;
	    else if(number>=0.4)
	    	p[4]++;
	    else if(number>=0.3)
	    	p[3]++;
	    else if(number>=0.2)
	    	p[2]++;
	    else if(number>=0.1)
	    	p[1]++;
	    else if(number>=0)
	    	p[0]++;
	}

	std::cout << "exponential(" << generator << "):" << std::endl;
	std::cout << std::fixed; std::cout.precision(1);

	for (int i=0; i<nintervals; ++i) {
		std::cout << float(i)/nintervals << "-" << float(i+1)/nintervals << ": ";
		std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
	}
}

void Test::normal(){
  int p[10]={};

  for (int i=0; i<nrolls; ++i) {
	double number = mmc->sampleNormal(5.0, 2.0);
	if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
  }

  std::cout << "normal_distribution (5.0,2.0):" << std::endl;

  for (int i=0; i<10; ++i) {
	std::cout << i << "-" << (i+1) << ": ";
	std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }
}

void Test::gamma(){
	int p[10]={};

	for (int i=0; i<nrolls; ++i) {
		double number = mmc->sampleGamma(2.0, 2.56);
		if (number<10) ++p[int(number)];
	}

	std::cout << "gamma_distribution (2.0,2.0):" << std::endl;

	for (int i=0; i<10; ++i) {
		std::cout << i << "-" << (i+1) << ": ";
		std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
	}
}

void Test::erlang(){
	int p[10]={};

	for (int i=0; i<nrolls; ++i) {
		double number = mmc->sampleErlang(2.0, 2);
		if (number<10) ++p[int(number)];
	}

	std::cout << "erlang_distribution (2.0,2):" << std::endl;

	for (int i=0; i<10; ++i) {
		std::cout << i << "-" << (i+1) << ": ";
		std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
	}
}

void Test::beta(){
	int p[10]={};

	for (int i=0; i<nrolls; ++i) {
		double number = mmc->sampleBeta(2.0, 7.0, 0, 10);
		if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
	}

	std::cout << "beta_distribution (2.0, 7.0, 0, 10):" << std::endl;

	for (int i=0; i<10; ++i) {
		std::cout << i << "-" << (i+1) << ": ";
		std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
	}
}

void Test::logNormal(){
	int p[10]={};

	for (int i=0; i<nrolls; ++i) {
		double number = mmc->sampleLogNormal(0, 1);
		if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
	}

	std::cout << "lognormal_distribution (0.0,1.0):" << std::endl;

	for (int i=0; i<10; ++i) {
		std::cout << i << "-" << (i+1) << ": ";
		std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
	}
}

void Test::weibull(){
  

  for (int i=1; i<50; ++i) {
		double number = mmc->sampleWeibull(5.0, 0.5 );
		std::cout << i << ": ";
		std::cout << number << std::endl;
	}
}	

void Test::triangular(){
	int p[10]={};

	for (int i=0; i<nrolls; ++i) {
		double number = mmc->sampleTriangular(-1, 1, 0); //0 1 0.5
		if ((number>=0.0)&&(number<10.0))++p[int(number)];
	}

	std::cout << "triangular_distribution (0.0,1.0, 0.5 ):" << std::endl;

	for (int i=0; i<10; ++i) {
		std::cout << i << "-" << (i+1) << ": ";
		std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
	}	
}

/*void Test::discrete(){
	std::vector<double>& weights = {20, 10, 30};
	int num_samples = 400;
	mmc->sampleDiscrete( weights );

	std::vector<size_t> counts(weights.size(), 0);
	for (size_t i = 0; i < num_samples; ++i) {
	 const int number = sampleDiscrete();
	 assert(number >= 0);
	 assert(number < static_cast<int>(weights.size()));
	 ++counts[number];
}

  std::cout << "counts:" << std::endl;
  for (size_t i = 0; i < weights.size(); ++i)
    cout << i << " (" << weights[i] << ") : "
         << std::string(counts[i], '*') << endl;

  cout << endl;
}
*/

