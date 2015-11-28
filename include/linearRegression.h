#ifndef LINEAR_REGRESSION_H_
#define LINEAR_REGRESSION_H_

#include <string>
#include <iostream>

using namespace std;

class Regression{
  friend ostream& operator<<(ostream&,const Regression&);

public:
  		Regression();
  		Regression(unsigned);
  		Regression(const Regression&);
  		~Regression();
  Regression&	operator=(const Regression&);

  inline unsigned getDim();

  double	evaluate(double*);		// return the output of h(x)
						  // recieves a vector of n dimension
  void		learn();

private:
  void		Copy(const Regression&);

  double*	theta;		// Vector theta
  unsigned	dim;		// Number of dimensions

};

inline unsigned
Regression::getDim() { return dim; }

#endif
