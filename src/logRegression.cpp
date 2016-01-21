#include <iostream>
#include "logRegression.h"
#include <float.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>

namespace Algorithm{

LogRegression::LogRegression(){
	dim = 0;
	theta = new double;
	theta_aux = new double;
	alpha = 1.0;
}

LogRegression::LogRegression(int dimensions, double alpha){
	if(dimensions<1){
		cerr << "Error: cannot create Regression of <1 dimensions" << '\n';
		return;
	}

	dim = dimensions;
	theta = new double[dimensions+1];
	theta_aux = new double[dimensions+1];
	for(unsigned i=0;i<=dimensions;++i){
		theta[i] = 0.0;
		theta_aux[i] = 0.0;
	}

	this->alpha = alpha;
}

double
LogRegression::sigmoid(const double x) const{
  double prueba = 1/(1+exp(-x));

  //std::cout << "Valor que devuelve la sigmoidea antes del return: " << prueba << '\n';

  return prueba;
}

void
LogRegression::train(const Trainning_Set& train_set){
  // Coste anterior.
	double c0 = 0.0;
	double* temp=new double[dim+1];
	//double alphaDivNum= alpha/train_set.size();
	double alphaDivNum= alpha;
	//cout << "sdaflkjssfd: " << alphaDivNum;
	unsigned k;
	k=0;
	std::ofstream file;
	file.open("exit.csv");
	do{
    	gradientDescent(temp, alphaDivNum, file, k, train_set);
    	k++;
    	//cout << "k: " << k << endl;
  }while(k<30000 && convergence(c0, train_set));

	std::cout << "k: " << k << "\n";
	file.close();
  delete[] temp;
}

double
LogRegression::cost(const Trainning_Set& train_set) const{
  // Sigmoid.
  double c, h = 0.0;
  unsigned n = train_set.size();
  //cout << "train_set.size(): " << n << endl;
  //cout << train_set.get_x(1,1) << endl;
  for(unsigned i=0; i<n; ++i){
    /*for(unsigned j=0; j<=dim; ++j){
    	//cout << "elemento que devuelve: " << train_set.get_x(i,j) << endl;
    	h += theta[j]*train_set.get_x(i,j);
    }
    //std::cout << "h antes: " << h << "\n";
    h = sigmoid(h);*/
    h = evaluate(train_set.get_x(i));
    //cout << "i: " << i << endl;
    //std::cout << "h despues de sigmoid: " << h << "\n";
    //std::cout << "logaritmo de h: " << log(h) << "\n";
    c += train_set.get_y(i)*log(h)-(1-train_set.get_y(i))*log(1-h);
    h=0.0;
  }
  return -c/n;
}

double
LogRegression::evaluate(const std::vector<double>& x) const{
	double h = 0.0;
	//double y = theta[0];
	for(unsigned j=0;j<=dim;++j){
		h += theta[j]*x[j];
	}

	h = sigmoid(h);

	return h;
}

bool
LogRegression::convergence(double& c0,const Trainning_Set& train_set) const{
  double c = 0.0;
  c = cost(train_set);
  bool r = std::abs(c-c0)>0.0000001;
  c0 = c;
  return r;
}
/*double
LogRegression::convergence(double& c0,const Trainning_Set& train_set) const{
  double c = 0.0;
  for(unsigned i=0;i<=dim;++i)
  	c+=abs(theta[i]-theta_aux[i]);
  return c;
}*/

void
LogRegression::gradientDescent(double *temp, double alphaDivNum, std::ofstream& file, unsigned k, const Trainning_Set& train_set){
  unsigned i;

	for(i=0;i<=dim;++i)
		temp[i]=0;

  // Recorrer vector
  unsigned m = train_set.size();
	for(i=0;i<=dim;++i){
		// Recorrer vector temp
		for(unsigned j=0;j<m;++j){
			temp[i] += (evaluate(train_set.get_x(j)) - 
				train_set.get_y(j))*train_set.get_x(j,i);
			
			
		}
		//cout<< "i: " << i << endl;
		//cout<< "temp[: " << i << "]: " << temp[i] << endl;
	}
	for(i=0;i<=dim;++i){
    // Copy last values of theta for convergence
		theta_aux[i]=theta[i];
		theta[i] -= alphaDivNum*temp[i];
		cout << "theta[" << i << "]: " << theta[i] << endl;
		if(k%10==0){
			if(i==0)
				file << theta[i] << "+";
			else if(i==dim)
				file << theta[i] << "*x \n";
			else
				file << theta[i] << "*x+";
		}
	}
	/*cout << "dim: " << dim << '\n';
	for(i=0;i<=dim;i++){
		cout << "theta[" << i << "]: " << theta[i] << '\n';
	}*/
	/*int kk;
	cin >> kk;*/
}

}
