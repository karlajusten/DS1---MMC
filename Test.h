/*
 * Test.h
 *
 *  Created on: 26 de ago de 2018
 *      Author: karla
 */

#ifndef TEST_H_
#define TEST_H_
#include <iostream>
#include <stdio.h>

#include "MMC.h"
#include <memory>
#include <cassert>
#include <vector>
#include <iterator>

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
	std::unique_ptr<MMC> mmc;
};

#endif /* TEST_H_ */
