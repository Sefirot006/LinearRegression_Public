#include "neuralNetwork.h"
#include <cmath>

namespace Algorithm{
	NeuralNetwork::NeuralNetwork(){
		dim = 0;
		unidadesOcultas = 0;
		capasOcultas = 0;
		lambda = 0;

	}

    void printMatrix(const ublas::matrix<double>& matrix) {
        cout << "-----Matrix-----" << endl;
        for (unsigned int i=0; i < matrix.size1(); i++) {
            cout << "{";
            for (unsigned int j=0; j < matrix.size2(); j++) {
                cout << matrix(i, j);
                if(j+1 != matrix.size2()) {
                    cout << ",";
                }
            }
            cout << "}," << endl;
        }
        cout << endl;
    }

	NeuralNetwork::NeuralNetwork(unsigned dim, unsigned capas, unsigned unidades, unsigned tamSalida, unsigned lambda, unsigned size)
            : theta1(dim+1,unidades+1),theta2(unidades+1)
            , d_1(size,unidades+1), d_2(size)
            , delta1(unidades+1), a(unidades+1) {
		this->dim = dim;
		capasOcultas = capas;
		unidadesOcultas = unidades+1;
		tamCapaSalida = tamSalida;
		this->lambda = lambda;

        delta2 = 0.0;
        a[0] = 1.0;
        h = 0.0;

        srand(time(NULL));
		//Rellenamos la matriz con numeros random entre 0 y 1
		for(unsigned i=0;i<theta1.size1();++i){
			for(unsigned j=0;j<theta1.size2();++j){
				theta1(i,j) = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			}
		}

		// Rellenamos la matriz2 con numeros random entre 0 y 1
		for(unsigned i=0;i<theta2.size();++i){
			theta2[i] = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		}

	}

	double NeuralNetwork::sigmoid(const double x) const{
	  double prueba = 1/(1+exp(-x));

	  //std::cout << "Valor que devuelve la sigmoidea antes del return: " << prueba << '\n';

	  return prueba;
	}

	// SI PONEMOS MAS CAPAS OCULTAS ESTO NO VA A FUNCIONAR BIEN
	// ESTA PREPARADO SOLO PARA UNA CAPA OCULTA
	double NeuralNetwork::forwardPropagation(const Trainning_Set& train_set, const unsigned elem){
		// Es un vector porq solo hay una capa oculta
		// si hubiesen mas tendria que convertirse en una matriz
		double parcial = 0.0;
		for(unsigned i=1;i<theta1.size2();++i){
			for(unsigned j=0;j<theta1.size1();++j){
				parcial += theta1(j,i)*train_set.get_x(elem,i);
			}
			a[i] = sigmoid(parcial);
			parcial = 0.0;
		}

		parcial = 0.0;
		for(unsigned k=0;k<theta2.size();++k){
			parcial += a[k]*theta2[k];
		}
		return sigmoid(parcial);
	}

	// La intencion de esta funcion es calcular la h(x)i
	double NeuralNetwork::evaluate(const std::vector<double>& x, unsigned k) const{
		double ev = 0.0;
		//TODO esta mal? revisar
		//for(unsigned i=0;i<theta2.size2();++i){
			//ev += x[i]*theta2(k,i);

		ev = sigmoid(ev);
		return ev;
	}

	//Funcion de coste sin la parte de la regularizacion
	double NeuralNetwork::costFunction(const Algorithm::Trainning_Set& train_set){
		double c, h, reg = 0.0;
		//El total de las capas son las capas ocultas + la capa de entrada y la de salida
		unsigned L = capasOcultas+2;

		//nº de unidades sin contar la bias en la capa l
		//Como solo hemos puesto una capa este dato se calcula de la siguiente manera
		unsigned sl = unidadesOcultas-1;

		//Cantidad de conjuntos de entrenamiento
		unsigned m = train_set.size();

		for(unsigned i=0; i<m;++i){
			// Si pensamos en que solo tenga una posible salida
			// Que seria juega o no juega

			//Hay que calcular la h(x)i
			//La intencion es que lo haga con esta funcion
			//Pero no se yo si lo hara bien o q
			h = forwardPropagation(train_set,i);
			c += train_set.get_y(i)*log(h) + (1 - train_set.get_y(i)) * log(1-(h));
		}
		c = -c/m;
		// a esto hay que sumarle lo de la regularizacion que no entiendo como cojones se calcula
		//No se si esta bien pero si esta bien dadme un pin!!si no...arreglelo!!
		for(unsigned l=1;l<L-1;++l){
			for(unsigned i=1;i<sl;++i){
				for(unsigned j=1;j<sl+1;++j){
					//Aqui como solo tenemos dos matrices de thetas por la cantidad de capas
					//ocultas que le hemos puesto (solo 1) pues accedo por un if y punto ;)
					if(l==1){
						reg += pow(theta1(j,i),2);
					}
					else if(l==2){
						reg += pow(theta1(j,i),2);
					}
				}
			}
		}

		reg = reg*(lambda/2*m);

		return reg+c;
	}

    void NeuralNetwork::backPropagation(const Algorithm::Trainning_Set& train_set){
        for(unsigned i=0;i<delta1.size();++i)
            delta1[i] = 0.0;

        delta2 = 0.0;

        for(unsigned i=0;i<d_1.size1();++i)
            for(unsigned j=0;j<d_1.size2();++j)
                d_1(i,j) = 0.0;

        for(unsigned i=0;i<d_2.size();++i)
            d_2[i] = 0.0;

        for(unsigned i=0;i<train_set.size();++i){
            h=forwardPropagation(train_set,i);

            // lower delta hidden layer
            for(unsigned j=0;j<delta1.size();j++)
                delta1[j] = theta2[j] * delta2;

            // lower delta output layer
            delta2 = h - train_set.get_y(i);

            // Upper delta input layer
            for(unsigned j=0;j<d_1.size2();++j)
                d_1(i,j) += train_set.get_x(i,j) * delta1[j];

            // Upper delta hidden layer
            d_2[i] += h * delta2;

        }
        // Partial derivatives of cost function: D(l)_ij
        for(unsigned j=0;j<d_1.size1();++j){
            for(unsigned k=0;k<d_1.size2();++k){
                // D(j,k) := DELTA(j,k)/trainset.size
                d_1(j,k) = d_1(j,k)/train_set.size();

                if(k!=0)
                    d_1(j,k) += theta2[k] * lambda;
            }
        }

        // Partial derivatives of cost function: D(l)_ij
        for(unsigned j=0;j<d_2.size();++j){
                d_2[j] = d_2[j]/train_set.size();
        }

    }

    void NeuralNetwork::gradientDescent(double alpha,const Algorithm::Trainning_Set& train_set){
        ublas::matrix<double> temp1(theta1.size1(),theta1.size2());	// matriz de pesos de la capa 1
		vector<double> temp2(theta2.size());
        unsigned cont=0;

        do{
            cont++;
            for(unsigned i=0;i<temp1.size1();++i)
                for(unsigned j=0;j<temp1.size2();++j)
                    temp1(i,j) = 0.0;

            for(unsigned i=0;i<temp2.size();++i)
                temp2[i] = 0.0;

            backPropagation(train_set);

            for(unsigned i=0;i<theta1.size1();++i){
                for(unsigned j=0;j<theta1.size2();++j){
                    temp1(i,j) = theta1(i,j);
                    theta1(i,j) -= alpha*d_1(i,j);
                }
            }
            for(unsigned i=0;i<theta2.size();++i){
                temp2[i] = theta2[i];
                theta2[i] -= alpha*d_2[i];
            }
        }while(cont < 5000 && convergence(temp1,temp2));

    }

    bool NeuralNetwork::convergence(const ublas::matrix<double>& temp1,const vector<double>& temp2){
        double conv=0.0;

        for(unsigned i=0;i<theta1.size1();++i){
            for(unsigned j=0;j<theta1.size2();++j){
                conv+= abs(temp1(i,j) - theta1(i,j));
            }
        }
        for(unsigned i=0;i<theta2.size();++i){
            conv+= abs(temp2[i] - theta2[i]);
        }
        cout << conv << endl;
        return conv > 0.0001*dim*unidadesOcultas*unidadesOcultas*tamCapaSalida;
    }
}
