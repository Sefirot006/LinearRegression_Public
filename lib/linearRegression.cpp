#include "linearRegression.h"

ostream&
operator<<(ostream& s,const Regression& reg){
	s << "Linear Regression: " << endl
		<< "Number of Dimensions: " << reg.dim << endl
		<< "Theta: " << endl;
	for(unsigned i=0;i<reg.dim;i++)
		s << i << ": " << reg.theta[i];
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

void
Regression::Copy(const Regression& reg){
	dim=reg.dim;
	theta=new double[dim];
	for(unsigned i=0;i<dim;++i)
		theta[i]=reg.theta[i];
}

double
Regression::evaluate(double* x){
	double y=theta[0];
	for(unsigned i=1;i<dim;++i)
		y+=theta[i]*x[i];
	return y;
}
