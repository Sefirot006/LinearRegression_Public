#include <iostream>
#include "perceptron.h"
#include <float.h>
#include "util.cpp"


using namespace std;

namespace Algorithm{

Perceptron::Perceptron(unsigned dim) {
	wheights= new double[dim+1]; // w0
  for(unsigned i=0;i<=dim;i++){
    wheights[i] = 0.0;
  }
}

std::vector<double>
Perceptron::train(int m, const Trainning_Set& train_set){

	unsigned n = train_set.size();

	double x, y, h, sum = 0;
	std::vector<double> updatedW;

	h =
	x =
	y = 0;

	int errCount = 0;
	int pErrs[n];
	int iPerrs = 0;

	// Train
	bool loop = true;
	for(unsigned i=0;i<m && loop;i++){

	    errCount = 0;

	    for (unsigned j=0; j < n; ++j) {
	        y = train_set.get_y(j);

	        //Saca el tamaño del train_set
	        int l = train_set.get_dim();
	        for (unsigned k=0; k<=l; ++k)
	          sum += wheights[k]*train_set.get_x(j,k);

	        h = sign(sum);

	        if((h==-1 && train_set.get_y(j)==1) || (h==1 && train_set.get_y(j)==-1))
						pErrs[errCount++] = j;
	    }

	    h = 0;
			if(errCount>0){
		    int rnd = rand()%errCount;
		    unsigned rndIndex = pErrs[rnd];
				int l = train_set.get_dim();
		    for (unsigned k=0; k <= l; ++k){
					wheights[k] = wheights[k]+train_set.get_y(rndIndex)*train_set.get_x(rndIndex,k);
	    	}

			} else loop=false;
	}

	unsigned l = train_set.get_dim();
	for(unsigned i=0;i<=l;i++) updatedW.push_back(wheights[i]);

	return updatedW;
}

}
