#include "linearRegression.h"

ostream&
operator<<(ostream& s,const Regression& reg){
	s << "Linear Regression: " << endl
		<< "Number of Dimensions: " << reg.dim << endl
		<< "Alpha: " << reg.alpha << endl;
		for(unsigned i=0;i<=reg.dim;i++)
			s << "Theta_" << i << ": " << reg.theta[i] << ",";
	s << endl;

	return s;
}

Regression::Regression(){
	dim=1;
	theta=new double;
	alpha=1.0;
}

Regression::Regression(unsigned dimensions,double alpha){
	if(dimensions==0){
		cerr << "Error: cannot create Regression of 0 dimensions" << endl;
		return;
	}

	dim=dimensions;
	theta=new double[dimensions+1];
	this->alpha=alpha;
}

Regression::Regression(const Regression& reg){
	Copy(reg);
}

Regression::~Regression(){
	dim=0;
	alpha=0.0;
	if(theta!=NULL)
		delete [] theta;
}

Regression& Regression::operator=(const Regression& reg){
	if(this!=&reg){
		(*this).~Regression();
		Copy(reg);
	}
	return *this;
}

void
Regression::Copy(const Regression& reg){
	dim=reg.dim;
	theta=new double[dim];
	for(unsigned i=0;i<=dim;++i)
		theta[i]=reg.theta[i];
}

double
Regression::evaluate(double* x){
	double y=theta[0];
	for(unsigned i=1;i<=dim;++i)
		y+=theta[i]*x[i];
	return y;
}

void
Regression::gradient_descent(const vector<Example>& train_set){
	double* temp=new double[dim+1];
	double alphaDivNum= alpha/dim;
	unsigned i;

	do{
		for(i=0;i<=dim;++i)
			temp[i]=0;

		// Recorrer vector ejemplos
		for(i=0;i<train_set.size();++i){
			// Recorrer vector temp
			for(unsigned j=0;j<=dim;++j)
				// temp_j = temp_j + (h(x_i) - y_i) * x_i
				temp[j] += (evaluate(train_set[i].first) - train_set[i].second) *train_set[i].first[j];
		}
		for(i=0;i<=dim;++i)
			// theta_i = theta_i - 1/m * alpha *temp_i
			theta[i] -= alphaDivNum*temp[i];

	}while(temp[0]!=0);
}
