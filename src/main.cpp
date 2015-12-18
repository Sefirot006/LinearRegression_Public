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
	cout << train;
	//Trainning_Set trainAux(train);
	//trainAux.normalize();
	//cout << trainAux;

	ofstream file;
	file.open("train_set_points");
	if(file)
		file<< train;

	reg.gradient_descent(train);
	return 1;
}
