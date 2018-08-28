/*
 * MMC.cpp
 *
 *  Created on: 15 de ago de 2018
 *      Author: karla
 *      Author: bruno
 */

#include "MMC.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


MMC::MMC() {  
	
	PCG_Parameters param;
	param.ling_seed = 0x4d595df4d0f33173;
	param.multiplier = 6364136223846793005u;
	param.increment = 1442695040888963407u;
	setRNGparameters(param);
}

MMC::MMC(const MMC& mmc_) {  
}

MMC::~MMC() {
	// TODO Auto-generated destructor stub
}

/*
 * Método de geração de número randômico utilizado: PCG-XSH-RR
 */
double  MMC::random(){

	uint64_t x = param.ling_seed;
	unsigned count = (unsigned)(x >> 59);
	//PCG_Parameters new_seed = getRNGparameters();
	param.ling_seed = x * param.multiplier + param.increment;
	//setRNGparameters(new_seed);
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

double MMC::sampleUniform(double min, double max){
	if ( min <0 || max <0 || max < min ) {
      throw "Incorrect params at uniform distribution method!";
   }   
	    uint64_t x = random();
	     if (max == 1.0 && min == 0.0)
	     	return ldexp(x, -32);  // pcg generate floats[0,1] nearest multiple of 1/2^32 
	    uint64_t m =  x * double(max - min); 
	    return (double) (m  >> 32) + min;    
}    

double MMC::sampleExponential(double mean){
	if( mean == 0 ) {
		throw "Division by zero condition at exponential distribution method!";
	}
	double x = random();
	return (1/mean)*exp((double)(-(x/mean)));
}

double MMC::sampleNormal(double mean, double stddev){
	if ( mean <=0 || stddev <=0 ) {
      throw "Incorrect params at Normal distribution method!";
   	}
	double x = random();
	double num = (x-mean);
	//std::cout << "num = "<< num << std::endl;
	//std::cout << "secondTerm = " << exp((double)-(num*num)/(2*stddev*stddev)) << std::endl;
	//std::cout << "firstTerm = " << (1/(stddev*sqrt(2*M_PI))) << std::endl;
	return (1/(stddev*sqrt(2*M_PI)))*exp((double)-(num*num)/(2*stddev*stddev));
}

double MMC::sampleGamma(double mean, double alpha){
	if ( mean <=0 || alpha <=0 ) {
      throw "Incorrect params at Gamma distribution method!";
   	}
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
double MMC::sampleErlang(double mean, int M){
	if ( mean <0 || M <=0 ) {
      throw "Incorrect params at Erlang distribution method!";
   }   
	  return this->sampleGamma(mean, M);  //Erlang is gamma where alpha is an integer; by Boost and GSL 
}

double MMC::sampleBeta(double alpha, double beta, double infLimit, double supLimit){
	
	 if ( alpha<=0.0 || beta<=0.0 || infLimit > supLimit || infLimit <0 || supLimit <0 ) {
	 	throw "Incorrect params at beta distribution method!";
	 }   
  	double term = (tgamma(alpha)*tgamma(beta));
	if( term == 0 ) {
		throw "Division by zero condition at beta distribution method!";
	}
	double x = sampleUniform(0.0, 1.0); 
	return (tgamma(alpha+beta)/term)*pow(x, alpha-1)*pow(1-x, beta-1);
}

double MMC::sampleWeibull(double alpha, double scale){
	if ( scale <=0 || alpha <=0 ) {
      throw "Incorrect params at Weibull distribution method!";
   	}
   	double x = random();
   	double m = pow (-log (x), 1 / scale);

   	return alpha * m;
}

double MMC::sampleLogNormal(double mean, double stddev){
	if ( mean <=0 || stddev <=0 ) {
      throw "Incorrect params at LogNormal distribution method!";
   	}
	double x = random();
	if( stddev == 0 || x == 0) {
		throw "Division by zero condition at logNormal distribution method!";
	}
	double num = log(x)-mean;
	return (1/(x*stddev*sqrt(2*M_PI)))*exp((double)-(num*num)/(2*stddev*stddev));
}

double MMC::sampleTriangular(double min, double mode, double max){
	if ( min <0 || max <0 || mode<0 ) {
      throw "Incorrect params at Triangular distribution method!";
   	}
	double w =  min - mode;
	double z =  max - mode;
	double r =  max - min;
	double x = random();
	if (x < (w/r))
		return min+sqrt(w*r*x);
	else
		return max-sqrt(z*r*(1.0 - x)); 
}

/*//  Algorithm by DavidPal O(1) instead of the naive O(log N)
//  https://github.com/DavidPal/discrete-distribution
//
double sampleDiscrete( const std::vector<double>& Prob) {
//const std::vector<double>& weights, const size_t num_samples
  discreta_rapida discreta( Prob );
  
return discreta()
};

namespace {
// fila
template<typename T, typename BidirectionalIterator>
class fila {
  public:
    fila(const BidirectionalIterator base)
      : base_(base), top_(base) { };

    void push(const T& element) {
      *top_ = element;
      ++top_;
    }

    T pop() {
      --top_;
      return *top_;
    }

    bool empty() {
      return top_ == base_;
    }

  private:
    const BidirectionalIterator base_;
    BidirectionalIterator top_;
};
}

//  algorithm by DavidPal O(1) instead of the naive O(log N)
class discreta_rapida {
  public:
    discreta_rapida(const std::vector<double>& pesos){
        criar_buckets();
    }

   double operator() (){
      const double number = MMC:sampleUniform(0.0, 1.0);
      size_t index = floor(buckets_.size() * number);

      const Bucket& bucket = buckets_[index];
      if (number < std::get<2>(bucket))
        return std::get<0>(bucket);
      else
        return std::get<1>(bucket);
    }
  
  private:
    typedef std::pair<double, double> Par;
    typedef std::tuple<double, double, uint64_t> Bucket;

    // List of probabilidades
    std::vector<double> probabilidades_;
    std::vector<Bucket> buckets_;


    void criar_buckets() {
      const size_t N = probabilidades_.size();
      if (N <= 0) {
        buckets_.emplace_back(0, 0, 0.0);
        return;
      }
      //Duas pilhas em um vetor: Primeira cresce do início; Segunda pilha cresce a partir do final.
      std::vector<Par> pares(N);
      fila<Par, std::vector<Par>::iterator>
        small(pares.begin());
      fila<Par, std::vector<Par>::reverse_iterator>
        large(pares.rbegin());

      //Divide probabilidades entre pequenas e grandes
      int i = 0;
      for (auto probability : probabilidades_) {
        if (probability < (1.0 / N)) {
          small.push(Par(probability, i));
        } else {
          large.push(Par(probability, i));
        }
        ++i;
      }

      buckets_.reserve(N);

      i = 0;
      while (!small.empty() && !large.empty()) {
        const Par s = small.pop();
        const Par l = large.pop();

        //  bucket misto
        buckets_.emplace_back(s.second, l.second,
                              s.first + static_cast<double>(i) / N);

        // Qual o comprimento das sobras
        const double sobras = s.first + l.first - static_cast<double>(1) / N;

        // Re-insira as sobras 
        if (sobras < (1.0 / N))
          small.push(Par(sobras, l.second));
        else
          large.push(Par(sobras, l.second));

        ++i;
      }

      // Criar buckets 
      while (!large.empty()) {
        const Par l = large.pop();
        // ultimo arg nao pode ser NaN;
        buckets_.emplace_back(l.second, l.second, 0.0);
      }
    }


}; */
