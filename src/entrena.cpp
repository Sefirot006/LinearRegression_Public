#include "linearRegression.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int
main(int argc,char** argv){
    if(argc!=2){
        cerr << "Error: Number of arguments is invalid." << endl
            << "./entrena [input file]" << endl;
        return 0;
    }

    // Trainning
	Trainning_Set train(argv[1]);
	LinearReg reg(train.get_dim(),0.00000001);
	//train.normalize();
	reg.normal_equation(train);

    reg.export_theta();

	return 1;
}
