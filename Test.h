/*
 * Test.h
 *
 *  Created on: 26 de ago de 2018
 *      Author: karla
 */

#ifndef TEST_H_
#define TEST_H_
#include "MMC.h"

class Test {
public:
	Test();
	virtual ~Test();
	void random();
	void uniform();
	void exponencial();
	void erlang();
	void normal();
	void beta();
	void gamma();
	void weibull();
	void logNormal();
	void triangular();
	void discrete();
private:
	MMC mmc;
};

#endif /* TEST_H_ */
