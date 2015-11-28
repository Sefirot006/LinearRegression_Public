#include "LinearRegression.h"

string
Regression::operator<<(ostream& s,const Regression& reg){
	string s;
	s << "Linear Regression: " << endl
		<< "Number of Dimensions: " << dim << endl
		<< "Theta: " << endl;
	for(unsigned i=0;i<dim;i++)
		s << i << ": " << theta[i];
	s << endl;

	return s;
}

Regression::Regression(){
	dim=1;
	theta=new double;
}

Regression::Regression(unsigned dimensions){
	if(dimensions==0){
		cerr << "Error: cannot create Regression of 0 dimensions" << endl;
		return;
	}

	dim=dimensions;
	theta=new double[dimensions];
}

Regression::Regression(const Regression& reg){
	Copy(reg);
}

Regression::~Regression(){
	dim=0;
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

double
Regression::evaluate(double* x){
	double y=theta[0];
	for(unsigned i=1;i<dim;++i)
		y+=theta[i]*x[i];
	return y;
}
