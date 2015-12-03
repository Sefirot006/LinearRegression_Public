#ifndef LINEAR_REGRESSION_H_
#define LINEAR_REGRESSION_H_

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;


class Regression{
  // Output operator
  friend ostream& operator<<(ostream&,const Regression&);

public:
  // Trainning example type
  // It has (first) an n+1 dimensional vector with the first value=1
  // and (second) the value of output
  typedef pair<double*, double> Example;

  		Regression();			// Void Constructor
  		Regression(unsigned,double);	// Constructor with dimensions and alpha
  		Regression(const Regression&);	// Copy Constructor
  		~Regression();			// Destructor
  Regression&	operator=(const Regression&);	// Assingment operator

  // Getters and setters
  inline unsigned get_dim();
  inline double	get_alpha();
  inline void	set_alpha(double a);

  double	evaluate(double*);	// return the output of h(x)
					  // recieves a vector of n dimension
  void		gradient_descent(const vector<Example>&); // Gradient descent learning function

private:
  void		Copy(const Regression&);
  double	convergence()const;

  double*	theta;		// Vector theta parameters of hypotesis
  double*	theta_aux;	// Auxiliar to calculate convergence
  unsigned	dim;		// Number of dimensions
  double	alpha;		// Trainning rate
};

inline unsigned
Regression::get_dim() { return dim; }

inline double
Regression::get_alpha() { return alpha; }

inline void
Regression::set_alpha(double a) { alpha=a; }

#endif
