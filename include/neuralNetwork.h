#ifndef NEU_NETWORK_H
#define NEU_NETWORK_H

#include <iostream>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <trainningSet.h>

using namespace std;
namespace ublas = boost::numeric::ublas;

namespace Algorithm{

	// Esta red neuronal esta hecha para que solo tenga una capa oculta
	// y que tenga una unidad en la capa oculta mas que los
	//datos de entrada que se le metan
	class NeuralNetwork {
		public:
			// dim,capasOcultas,unidadesOcultas,tamSalida,lambda
			NeuralNetwork(unsigned, unsigned, unsigned, unsigned,unsigned,unsigned);
			void train(const Algorithm::Trainning_Set&);
			double forwardPropagation(const Algorithm::Trainning_Set&, const unsigned);
			void backPropagation(const Algorithm::Trainning_Set&);
            double sigmoid(const double x) const;
			double costFunction(const Algorithm::Trainning_Set&);
			double evaluate(const std::vector<double>&, unsigned) const;
            void gradientDescent(double alpha,const Algorithm::Trainning_Set& train_set);
            bool convergence(const ublas::matrix<double>&,const vector<double>&);

            inline double getH()const;
      private:
			NeuralNetwork();	//constructor vacio
			ublas::matrix<double> theta1;	// matriz de pesos de la capa 1
			vector<double> theta2;	// matriz de pesos de la capa 2

            vector<double> delta1;    // Errors hidden layer
            double delta2;     // Errors output layer
            ublas::matrix<double> d_1;       // Delta uppercase input layer
            vector<double> d_2;       // Delta uppercase hidden layer

            vector<double> a;          // Activation hidden layer
			double h;          // Activation output layer
            unsigned dim;	// dimensiones
			unsigned unidadesOcultas;	// unidades que tendra la capa oculta
			unsigned capasOcultas;	//Capas ocultas que tendra la red
			unsigned tamCapaSalida;	//Tamaño de la capa de salida / clases que tendra de salida las redes
			unsigned lambda;

	};
    inline double
    NeuralNetwork::getH()const { return h; }
}



#endif // NEU_NETWORK_H
