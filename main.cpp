
/**
 *
 */

#include <stdio.h>
#include "MMC.h"

using namespace std;

#define buffer_size 512

int main() {

	MMC mmc;
	uint32_t buffer[buffer_size];

	MMC::RNG_Parameters seed;
	seed.ling_seed = 0xb4a10f2ad63c43c1;

	mmc.setRNGparameters(seed);

	while (1) {

	    for (int k = 0; k < buffer_size; k++)
	    	buffer[k] = mmc.random();
	    fwrite((void *)buffer, sizeof(buffer), 1, stdout);

	}

	return 0;
}
