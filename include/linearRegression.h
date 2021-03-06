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

class LinearReg{
  // Output operator
  friend ostream& operator<<(ostream&,const LinearReg&);

public:
  LinearReg(int,double); // Constructor with dimensions and alpha
  LinearReg(const LinearReg&); // Copy Constructor
  ~LinearReg(); // Destructor
  LinearReg& operator=(const LinearReg&); // Assingment operator

  // Getters and setters
  inline unsigned get_dim() const;
  inline double get_alpha() const;
  inline void set_alpha(double a);

  double evaluate(const vector<double>&) const; // Recieves a vector of n dimension and returns the output of h(x)
  void gradient_descent(const Trainning_Set&); // Gradient descent learning function
  void normal_equation(const Trainning_Set&);  // Normal equation method
private:
  LinearReg(); // Void Constructor
  void Copy(const LinearReg&);
  double convergence() const;
  void printMatrix(const ublas::matrix<double>&) const;
  bool inverse(const ublas::matrix<double>& mat,
                ublas::matrix<double>& inverse)const; // Calculate the inverse matrix with LU factorization

  double* theta; // Vector theta parameters of hypotesis
  double* theta_aux; // Auxiliar to calculate convergence
  unsigned dim; // Number of dimensions
  double alpha; // Trainning rate
  static const int maxIter = 30000;
  //static constexpr double minConv = 0.0001;
  static constexpr double minConv = 0.0000000001;
};

//////////////////
// INLINE METHODS
//////////////////

inline unsigned
LinearReg::get_dim()const { return dim; }

inline double
LinearReg::get_alpha()const { return alpha; }

inline void
LinearReg::set_alpha(double a) { alpha=a; }

#endif
