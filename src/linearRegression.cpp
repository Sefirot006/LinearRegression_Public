#include "linearRegression.h"

namespace Algorithm{

ostream&
operator<<(ostream& s,const Algorithm::LinearReg& reg){
    s << "Linear Regression: " << endl
        << "Number of Dimensions: " << reg.dim << endl
        << "Lambda: " << reg.lambda << endl;
        for(unsigned i=0;i<=reg.dim;i++)
            s << "Theta_" << i << ": " << reg.theta[i] << ",";
    s << endl;

    return s;
}

LinearReg::LinearReg(){
    dim=0;
    theta=new double;
    lambda=1.0;
}

LinearReg::LinearReg(int dimensions,double lambda){
    if(dimensions<1){
        cerr << "Error: cannot create LinearReg of <1 dimensions" << endl;
        return;
    }

    dim=dimensions;
    theta=new double[dimensions+1];
    for(unsigned i=0;i<=dimensions;++i){
        theta[i]=0.0;
    }
    this->lambda=lambda;
}

LinearReg::LinearReg(const LinearReg& reg){
    Copy(reg);
}

LinearReg::~LinearReg(){
    dim=0;
    lambda=1.0;
    if(theta!=NULL)
        delete [] theta;
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
    lambda=reg.lambda;
    theta=new double[dim+1];
    for(unsigned i=0;i<=dim;++i)
        theta[i]=reg.theta[i];
}

double
LinearReg::evaluate(const vector<double>& x)const{
    double y=theta[0];
    for(unsigned i=1;i<=dim;++i)
        y+=theta[i]*x[i];
    return y;
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
LinearReg::normal_equation(const Trainning_Set& train_set,bool regularization){
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

    if(regularization){
        // lambda_matrix
        ublas::matrix<double> lambda_matrix(X.size1(),X.size1());
        ublas::zero_matrix<double> zeroMatrix(X.size1(),X.size1());

        lambda_matrix = zeroMatrix;

        // Initialize lambda_matrix
        for(unsigned i=1; i <X.size1(); ++i)
            lambda_matrix(i,i) = lambda;

        // Add the regularization expression before the inverse operation
        X += lambda_matrix;
    }

    inverse(X,A);
    // A = A · X^t
    A=ublas::prod(A,X_t);
    // y = A · y
    y=ublas::prod(A,y);

    // Copy values to theta
    ofstream file;
    file.open("exit.csv");
    for(unsigned i=0;i<=dim;++i){
        theta[i]=y[i];
        if(i==0)
            file << theta[i] << "+";
        else if(i==dim)
            file << theta[i] << "*x, ";
        else
            file << theta[i] << "*x+";
    }
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
