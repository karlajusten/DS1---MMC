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
	void exponencial();
	void normal();
	void beta();
	void gamma();
	void logNormal();
private:
	MMC mmc;
};

#endif /* TEST_H_ */
