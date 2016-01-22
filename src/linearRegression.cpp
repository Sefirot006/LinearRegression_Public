#include "linearRegression.h"

namespace Algorithm{

ostream&
operator<<(ostream& s,const Algorithm::LinearReg& reg){
    s << "Linear Regression: " << endl
        << "Number of Dimensions: " << reg.dim << endl
        << "Alpha: " << reg.alpha << endl;
        for(unsigned i=0;i<=reg.dim;i++)
            s << "Theta_" << i << ": " << reg.theta[i] << ",";
    s << endl;

    return s;
}

LinearReg::LinearReg(){
    dim=0;
    theta=new double;
    theta_aux=new double;
    alpha=1.0;
}

LinearReg::LinearReg(int dimensions,double alpha){
    if(dimensions<1){
        cerr << "Error: cannot create LinearReg of <1 dimensions" << endl;
        return;
    }

    dim=dimensions;
    theta=new double[dimensions+1];
    theta_aux=new double[dimensions+1];
    for(unsigned i=0;i<=dimensions;++i){
        theta[i]=0.0;
        theta_aux[i]=0.0;
    }

    this->alpha=alpha;
}

LinearReg::LinearReg(const LinearReg& reg){
    Copy(reg);
}

LinearReg::~LinearReg(){
    dim=0;
    alpha=0.0;
    if(theta!=NULL)
        delete [] theta;
    if(theta_aux!=NULL)
        delete [] theta_aux;
}

LinearReg& LinearReg::operator=(const LinearReg& reg){
    if(this!=&reg){
        (*this).~LinearReg();
        Copy(reg);
    }
    return *this;
}

void
LinearReg::Copy(const LinearReg& reg){
    dim=reg.dim;
    theta=new double[dim+1];
    theta_aux=new double[dim+1];
    for(unsigned i=0;i<=dim;++i)
        theta[i]=reg.theta[i];
}

double
LinearReg::convergence()const{
    double conv=0.0;
    for(unsigned i=0;i<=dim;++i)
        conv+=abs(theta[i]-theta_aux[i]);
    return conv;
}

double
LinearReg::evaluate(const vector<double>& x)const{
    double y=theta[0];
    for(unsigned i=1;i<=dim;++i)
        y+=theta[i]*x[i];
    return y;
}

void
LinearReg::gradient_descent(const Trainning_Set& train_set){
    double* temp=new double[dim+1];
    double alphaDivNum= alpha/train_set.size();
    unsigned i,k;
    k=0;

    ofstream file;
    file.open("exit.csv");

    Trainning_Set trainAux(train_set);
    trainAux.normalize();
    cout << trainAux;

    do{
        for(i=0;i<=dim;++i)
            temp[i]=0;

        // Recorrer vector temp
        for(unsigned j=0;j<=dim;++j)
            // Recorrer vector ejemplos
            for(i=0;i<trainAux.size();++i)
                // temp_j = temp_j + (h(x_i) - y_i) * x_i
                temp[j] += (evaluate(trainAux.get_x(i)) - trainAux.get_y(i)) *trainAux.get_x(i,j);

        for(i=0;i<=dim;++i){
            // Copy last valueofstream file;
            theta_aux[i]=theta[i];
            // theta_i = theta_i - 1/m * alpha *temp_i
            theta[i] -= alphaDivNum*temp[i];
            //if(k%10==0){
                if(i==0)
                    //file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "+";
                    file << theta[i] << "+";
                else if(i==dim)
                    //file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "*x, ";
                    //file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "*x, ";
                    file << theta[i] << "*x, ";
                else
                    //file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "*x+";
                    //file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "*x+";
                    file << theta[i] << "*x+";
            //}
        }
        //if(k%100==0)
        //    file << endl;
        k++;
    }while(k<maxIter && (convergence() > minConv*dim));

    cout << k << endl;
    file.close();
    delete [] temp;
}


void LinearReg::printMatrix(const ublas::matrix<double>& matrix)const {
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

void
LinearReg::normal_equation(const Trainning_Set& train_set){
	ublas::matrix<double> X (train_set.size(),train_set.get_dim()+1);
	ublas::matrix<double> X_t (train_set.get_dim()+1,train_set.size());
	ublas::vector<double> y (train_set.size());

	// Obtaining X and transpose of X
	for(unsigned i=0; i < train_set.size(); ++i){
		for(unsigned j=0; j <= train_set.get_dim(); ++j){
			X(i,j) = train_set.get_x(i,j);
			X_t(j,i) = train_set.get_x(i,j);
		}
        y(i) = train_set.get_y(i);
	}
	// X = X · X^t
	X=ublas::prod(X_t,X);

    // A = X^-1
    ublas::matrix<double> A(X.size1(),X.size2());
	inverse(X,A);

    // A = A · X^t
    A=prod(A,X_t);
	// y = A · y
    y=prod(A,y);

    // Copy values to theta
    ofstream file;
    file.open("exit.csv");
    for(unsigned i=0;i<=dim;++i){
        theta[i]=y[i];
        if(i==0)
            file << theta[i] << "+";
        else if(i==dim)
            file << theta[i] << "*x**2, ";
        else
            file << theta[i] << "*x+";
    }
    /* Prueba funcion inverse
	ublas::matrix<double> aux2(4,4),aux3(4,4);
    aux2(0,0)=-1; aux2(0,1)=3; aux2(0,2)=1; aux2(0,3)=-1;
    aux2(1,0)=-4; aux2(1,1)=-10; aux2(1,2)=0; aux2(1,3)=4;
	aux2(2,0)=0; aux2(2,1)=7; aux2(2,2)=-2; aux2(2,3)=-4;
	aux2(3,0)=-7; aux2(3,1)=-14; aux2(3,2)=1; aux2(3,3)=5;
	printMatrix(aux2);
	inverse(aux2,aux3);
	aux3*=8;
	printMatrix(aux3);
	*/
}

bool
LinearReg::inverse(const ublas::matrix<double>& mat,
                    ublas::matrix<double>& inverse)const{
    using namespace ublas;

 	typedef permutation_matrix<std::size_t> pmatrix;
 	// create a working copy of the input
 	matrix<double> A(mat);
 	// create a permutation matrix for the LU-factorization
 	pmatrix pm(A.size1());

 	// perform LU-factorization
 	int res = lu_factorize(A,pm);
    if( res != 0 ) return false;

 	// create identity matrix of "inverse"
 	inverse.assign(identity_matrix<double>(A.size1()));

 	// backsubstitute to get the inverse
 	lu_substitute(A, pm, inverse);

	return true;
}

}
