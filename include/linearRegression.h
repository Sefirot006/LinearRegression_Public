#ifndef LINEAR_REGRESSION_H_
#define LINEAR_REGRESSION_H_

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

class Trainning_Set{
  friend ostream& operator<<(ostream&,const Trainning_Set&);
public:
  inline	Trainning_Set();			// Void constructor
  		Trainning_Set(const char*,int);		// Constructor with the name of a file to read
  inline 	~Trainning_Set();
  inline	Trainning_Set(const Trainning_Set&);	// Copy constructor
  Trainning_Set& operator=(const Trainning_Set&); 	// Assignment operator

  double 	get_x(int,int) const;
  double  	get_y(int pos) const;
  inline int	get_dim() const;
  const vector<double>& get_x(int) const;
private:
  inline bool	bound_check(int,int) const;
  void		insert(const string&);

  vector<pair<vector<double>, double> > set;	// Trainning set
  int 		dim;				// Dimensions
};

inline
Trainning_Set::Trainning_Set(): set(),dim(0)
{  }

inline
Trainning_Set::Trainning_Set(const Trainning_Set& ts): set(ts.set),dim(ts.dim)
{ }

inline
Trainning_Set::~Trainning_Set() { dim=0; }

inline int
Trainning_Set::get_dim() const { return dim; }

inline bool
Trainning_Set::bound_check(int pos,int tam) const
{ return pos>0 && pos<=tam; }

class Regression{
  // Output operator
  friend ostream& operator<<(ostream&,const Regression&);

public:
  // Trainning example type
  // It has (first) an n+1 dimensional vector with the first value=1
  // and (second) the value of output
  typedef pair<double*, double> Example;

  		Regression(int,double);		// Constructor with dimensions and alpha
  		Regression(const Regression&);	// Copy Constructor
  		~Regression();			// Destructor
  Regression&	operator=(const Regression&);	// Assingment operator

  // Getters and setters
  inline unsigned get_dim()const;
  inline double	get_alpha()const;
  inline void	set_alpha(double a);

  double	evaluate(const double*const)const;	// return the output of h(x)
					  		// recieves a vector of n dimension
  void		gradient_descent(const vector<Example>&); // Gradient descent learning function

private:
    		Regression();			// Void Constructor
  void		Copy(const Regression&);
  double	convergence()const;

  double*	theta;		// Vector theta parameters of hypotesis
  double*	theta_aux;	// Auxiliar to calculate convergence
  unsigned	dim;		// Number of dimensions
  double	alpha;		// Trainning rate
};

inline unsigned
Regression::get_dim()const { return dim; }

inline double
Regression::get_alpha()const { return alpha; }

inline void
Regression::set_alpha(double a) { alpha=a; }

#endif
