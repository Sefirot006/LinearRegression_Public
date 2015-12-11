#include "linearRegression.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int
main(int argc,char** argv){
	Regression reg(1,0.00000001);
	cout << reg;

	Trainning_Set train(argv[1],1);

	reg.gradient_descent(train);

	cout << train;

	return 1;
}
