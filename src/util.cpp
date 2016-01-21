#ifndef ALGORITHM_UTIL
#define ALGORITHM_UTIL

#include <iostream>

namespace Algorithm{

int sign(double n){
	// if (n > 0) return 1;
	// if (n < 0) return -1;
	// return 0;
	return ((n>=0) ? 1 : -1);
}

}

#endif // ALGORITHM_UTIL
