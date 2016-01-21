#include "perceptron.h"
#include "logRegression.h"
#include "neuralNetwork.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <trainningSet.h>

using namespace std;

int
main(int argc,char** argv){
	// Para la reg. lineal
	// LinearReg reg(1,0.00000001);
	// cout << reg;
	//
	// Trainning_Set train(argv[1]);
	// //train.normalize();
	// cout << train;
	//
	// //Trainning_Set trainAux(train);
	// //trainAux.normalize();
	// //cout << trainAux;
	// //train.normalize();
	// //cout << train;
	//
	// ofstream file;
	// file.open("train_set_points");
	// if(file)
	// 	file<< train;
	//
	// //reg.gradient_descent(train);
	// reg.normal_equation(train);
	//

	//Para el perceptron
	Algorithm::Perceptron perceptron(1);
	Algorithm::Trainning_Set train(argv[1]);
	std::vector<double> pesos;
	pesos = perceptron.train(200, train);
	std::cout << pesos[0] << ", " << pesos[1] << ", " << pesos[2] << '\n';

	//Para la regresion logistica
	// Algorithm::LogRegression logRegresion(2,0.01);
	//
	// Algorithm::Trainning_Set train(argv[1]);
	// //cout << "train.size(): " << train.size() << endl;
	// //cout << "train.0: " << train.get_x(0,1) << endl;
	// cout << train;
	//
	// train.normalize();
	// //cout << train;
	//
	// logRegresion.train(train);
	// cout << train;


	//Para las redes neuronales
	//dim,capas,unidades,tamSalida,lambda

	// Algorithm::Trainning_Set train(argv[1]);
	// Algorithm::NeuralNetwork neuralNetwork(2,1,2,1,0,train.size());
	//
  //   double alpha = 0.001;
	//
	// neuralNetwork.gradientDescent(alpha,train);
	//
	//
  //   cout << "1:" << neuralNetwork.forwardPropagation(train,0) << endl;
  //   cout << "0:" << neuralNetwork.forwardPropagation(train,1) << endl;
  //   cout << "0:" << neuralNetwork.forwardPropagation(train,2) << endl;
  //   cout << "1:" << neuralNetwork.forwardPropagation(train,3) << endl;
	//train.normalize();

	/*cout << train << endl;
	cout << "train_set.get_x(elem).size(): " << train.get_x(0).size() << endl;
	cout << "elemento1: " << train.get_x(0,0) << endl;
	cout << "elemento2: " << train.get_x(0,1) << endl;
	cout << "elemento3: " << train.get_x(0,2) << endl;
	int kk;
	cin >> kk;*/

	// Algorithm::LogRegression logRegresion(1,0.00001);
	//
	// Algorithm::Trainning_Set train(argv[1]);
	// cout << train;
	// train.normalize();
	// cout << train;
	//
	// logRegresion.train(train);

	return 1;
}
