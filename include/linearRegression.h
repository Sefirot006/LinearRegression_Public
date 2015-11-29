#ifndef LINEAR_REGRESSION_H_
#define LINEAR_REGRESSION_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Regression{
  friend ostream& operator<<(ostream&,const Regression&);

public:
  typedef pair<double*, double> Example;
  		Regression();
  		Regression(unsigned,double);	// Constructor with dimensions and alpha
  		Regression(const Regression&);
  		~Regression();
  Regression&	operator=(const Regression&);

  inline unsigned get_dim();
  inline double	get_alpha();
  inline void	set_alpha(double a);

  double	evaluate(double*);	// return the output of h(x)
					  // recieves a vector of n dimension
  void		gradient_descent(const vector<Example>&);

private:
  void		Copy(const Regression&);

  double*	theta;		// Vector theta parameters
  unsigned	dim;		// Number of dimensions
  double	alpha;
};

inline unsigned
Regression::get_dim() { return dim; }

inline double
Regression::get_alpha() { return alpha; }

inline void
Regression::set_alpha(double a) { alpha=a; }

#endif
