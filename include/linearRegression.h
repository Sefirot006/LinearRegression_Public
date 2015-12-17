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
  inline Trainning_Set();  // Void constructor
  Trainning_Set(const char*,int); // Constructor with the name of a file to read
  inline ~Trainning_Set();
  inline Trainning_Set(const Trainning_Set&); // Copy constructor
  Trainning_Set& operator=(const Trainning_Set&); // Assignment operator

  double get_x(int,int) const;  // get x_i of a training example
  double get_y(int pos) const;
  inline int get_dim() const;
  inline int size()const;
  const vector<double>& get_x(int) const; // get vector of x's of a trainngin example

  void normalize();                   // Normalize features
  void normalizeTrainingSet();        // Normalize features
private:
  void normalize_y();                 // Normalize y
  void normalize_x(int);              // Normalize vector x features
  void normalizeTrainingSet_y();      // Normalize y
  void normalizeTrainingSet_x(int);   // Normalize vector x features
  inline bool bound_check(int,int) const;
  void insert(const string&);

  vector<pair<vector<double>, double> > set; // Trainning set
  int dim; // Dimensions
};

class Regression{
  // Output operator
  friend ostream& operator<<(ostream&,const Regression&);

public:
  Regression(int,double); // Constructor with dimensions and alpha
  Regression(const Regression&); // Copy Constructor
  ~Regression(); // Destructor
  Regression& operator=(const Regression&); // Assingment operator

  // Getters and setters
  inline unsigned get_dim()const;
  inline double get_alpha()const;
  inline void set_alpha(double a);


  double evaluate(const vector<double>&)const; // Recieves a vector of n dimension and returns the output of h(x)
  void gradient_descent(const Trainning_Set&); // Gradient descent learning function
private:
  Regression(); // Void Constructor
  void Copy(const Regression&);
  double convergence()const;

  double* theta; // Vector theta parameters of hypotesis
  double* theta_aux; // Auxiliar to calculate convergence
  unsigned dim; // Number of dimensions
  double alpha; // Trainning rate
  static const int maxIter = 30000;
  static constexpr double minConv = 0.0001;
};

//////////////////
// INLINE METHODS
//////////////////

inline
Trainning_Set::Trainning_Set(): set(),dim(0)
{ }

inline
Trainning_Set::Trainning_Set(const Trainning_Set& ts): set(ts.set),dim(ts.dim)
{ }

inline
Trainning_Set::~Trainning_Set() { dim=0; }

inline int
Trainning_Set::get_dim() const { return dim; }

inline int
Trainning_Set::size() const { return set.size(); }

inline bool
Trainning_Set::bound_check(int pos,int tam) const
{ return pos>0 && pos<=tam; }

inline unsigned
Regression::get_dim()const { return dim; }

inline double
Regression::get_alpha()const { return alpha; }

inline void
Regression::set_alpha(double a) { alpha=a; }

#endif
