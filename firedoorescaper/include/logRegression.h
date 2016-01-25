#ifndef LOG_REGRESSION_H
#define LOG_REGRESSION_H

#include <iostream>
#include <vector>
#include <trainningSet.h>

using namespace std;

namespace Algorithm{

class LogRegression {

public:
	LogRegression(int, double);
  void train(const Algorithm::Trainning_Set&);
  double sigmoid(const double x) const;
  double cost(const Algorithm::Trainning_Set&) const;
  double evaluate(const std::vector<double>&) const;
  bool convergence(double&, double&, const Algorithm::Trainning_Set&) const;
  //double convergence(double&,const Algorithm::Trainning_Set&) const;
  void gradientDescent(double*, double, std::ofstream&, unsigned, const Trainning_Set&);
  double* getTheta() const;

private:
  LogRegression(); // Void constructor
  unsigned dim; // Number of dimesions
  double* theta;	     // Vector theta parameters of hypotesis
  double*	theta_aux;	 // Auxiliar to calculate convergence
  double alpha;		     // Trainning rate
};

}

#endif // LOG_REGRESSION_H
