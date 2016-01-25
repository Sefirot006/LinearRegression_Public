#ifndef TRAINNING_SET_H_
#define TRAINNING_SET_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace Algorithm{

class Trainning_Set{
  friend ostream& operator<<(ostream&,const Trainning_Set&);
public:
  inline Trainning_Set();         // Void constructor
  Trainning_Set(const char*);     // Constructor with the name of a file to read
  Trainning_Set(const vector<string>);     // Constructor to firedoor
  inline ~Trainning_Set();
  Trainning_Set(const Trainning_Set&);// Copy constructor
  Trainning_Set& operator=(const Trainning_Set&); // Assignment operator

  double get_x(int,int) const;        // get x_i of a training example
  double get_y(int pos) const;
  inline int get_dim() const;
  inline int size()const;
  const vector<double>& get_x(int) const; // get vector of x's of a trainngin example
  void normalize_x(int);              // Normalize vector x features
  void normalize();                   // Normalize features
  void delete_last();
private:
  void normalize_y();                 // Normalize y
  
  inline bool bound_check(int,int) const;
  void insert(const string&);

  vector<pair<vector<double>, double> > set;  // Trainning set
  int dim; // Dimensions
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
{ return pos>=0 && pos<=tam; }

}

#endif
