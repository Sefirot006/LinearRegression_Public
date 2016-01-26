#ifndef TRAINNING_SET_H_
#define TRAINNING_SET_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

namespace Algorithm{

class Trainning_Set{
  friend ostream& operator<<(ostream&,const Trainning_Set&);
public:
  inline Trainning_Set();         // Void constructor
  Trainning_Set(const char*);     // Constructor with the name of a file to read
  inline ~Trainning_Set();
  Trainning_Set(const Trainning_Set&);// Copy constructor
  Trainning_Set& operator=(const Trainning_Set&); // Assignment operator

  double get_x(int,int) const;        // get x_i of a training example
  double get_y(int pos) const;
  inline int get_dim() const;
  inline int size()const;
  const vector<double>& get_x(int) const; // get vector of x's of a trainngin example

  void normalize();                   // Normalize features
  void NLT_pow(unsigned x,unsigned exp);          // Non linear transform, select one feature and pow it
  void NLT_product(unsigned x1,unsigned x2);      // Non linear transform, producto of two features

  vector<double> avg;       // Average of all features from x_1 to x_n and Y
  vector<double> range;     // Range of all features from x_1 to x_n and Y
private:
  void normalize_x(int);              // Normalize vector x features
  inline bool bound_check(int,int) const;
  void insert(const string&);
  void resize();                      // Resize avg and range to a new dim
  void stats(unsigned x);             // Calculate range and average of features

  vector<pair<vector<double>, double> > set;  // Trainning set
  int dim; // Dimensions
};

//////////////////
// INLINE METHODS
//////////////////

inline
Trainning_Set::Trainning_Set(): set(),dim(0),avg(),range()
{ }

inline
Trainning_Set::Trainning_Set(const Trainning_Set& ts)
    : set(ts.set),dim(ts.dim),avg(ts.avg),range(ts.range)
{ }

inline
Trainning_Set::~Trainning_Set() { dim=0; }

inline int
Trainning_Set::get_dim() const { return dim; }

inline int
Trainning_Set::size() const { return set.size(); }

inline bool
Trainning_Set::bound_check(int pos,int tam) const
{ return pos>=0 && pos<=tam; }

}

#endif
