
/**
 *
 */

#include <iostream>
#include "MMC.h"

using namespace std;

int main() {

	MMC mmc;

	for(int x = 0; x < 20; x++){
	cout << "random: " << mmc.random() <<  endl; // prints !!!Hello World!!!
	}

	return 0;
}
