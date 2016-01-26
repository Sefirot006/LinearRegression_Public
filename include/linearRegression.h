#ifndef LINEAR_REGRESSION_H_
#define LINEAR_REGRESSION_H_

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <trainningSet.h>

//#define BOOST_UBLAS_NDEBUG 1
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
namespace ublas = boost::numeric::ublas;

namespace Algorithm{

class LinearReg{
  // Output operator
  friend ostream& operator<<(ostream&,const LinearReg&);

public:
  LinearReg(int,double); // Constructor with dimensions and lambda
  LinearReg(const LinearReg&); // Copy Constructor
  ~LinearReg(); // Destructor
  LinearReg& operator=(const LinearReg&); // Assingment operator

  // Getters and setters
  inline unsigned get_dim() const;
  inline double get_lambda() const;
  inline void set_lambda(double a);

  double evaluate(const vector<double>&) const; // Recieves a vector of n dimension and returns the output of h(x)
  void normal_equation(const Trainning_Set&,bool);  // Normal equation method regularized
private:
  LinearReg(); // Void Constructor
  void Copy(const LinearReg&);
  void printMatrix(const ublas::matrix<double>&) const;
  bool inverse(const ublas::matrix<double>& mat,
                ublas::matrix<double>& inverse)const; // Calculate the inverse matrix with LU factorization

  double* theta; // Vector theta parameters of hypotesis
  unsigned dim; // Number of dimensions
  static const int maxIter = 30000;
  // lamda_constant
  double lambda;
};

//////////////////
// INLINE METHODS
//////////////////

inline unsigned
LinearReg::get_dim()const { return dim; }

inline double
LinearReg::get_lambda()const { return lambda; }

inline void
LinearReg::set_lambda(double a) { lambda=a; }

}

#endif
