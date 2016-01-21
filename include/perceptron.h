#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <trainningSet.h>

using namespace std;

namespace Algorithm{

class Perceptron {

public:
	Perceptron(unsigned);
	std::vector<double> train(int, const Trainning_Set&);
private:
	double*	wheights;		// Vector wheights parameters of hypotesis
};

}

#endif // PERCEPTRON_H
