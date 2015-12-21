#include "linearRegression.h"

ostream&
operator<<(ostream& s,const Regression& reg){
    s << "Linear Regression: " << endl
        << "Number of Dimensions: " << reg.dim << endl
        << "Alpha: " << reg.alpha << endl;
        for(unsigned i=0;i<=reg.dim;i++)
            s << "Theta_" << i << ": " << reg.theta[i] << ",";
    s << endl;

    return s;
}

ostream&
operator<<(ostream& s,const Trainning_Set& t){
    for(unsigned i=0;i<t.set.size();++i){
        for(unsigned j=1;j<t.set[i].first.size();++j)
            s << t.set[i].first[j] << ",";
        s << t.set[i].second << endl;
    }
    return s;
}

//TODO ajustar parametro dimensiones automatico
Trainning_Set::Trainning_Set(const char* filename,int dimensions): set(){
    if(dimensions<1){
        cerr << "Error: cannot create Trainning Set of <1 dimensions" << endl;
        return;
    }else
        dim=dimensions;

    ifstream file;
    file.open(filename);
    if(file){
        string read;
        while(!file.eof()){
            getline(file,read);
            if(!read.empty())
                insert(read);
        }
        file.close();
    }else
        cerr << "Error al abrir el archivo "<< filename << endl;
}
/*
void
Trainning_Set::insert(const string& str){
    vector<double> x;
    x.push_back(1.0);
    string::size_type pos,last_pos;
    pos=0;
    last_pos=0;
    while(pos!=string::npos){
        pos=str.find(',',last_pos);
        if(pos!=string::npos){
        	x.push_back(stod(str.substr(last_pos,pos)));
        	last_pos=pos;
        	last_pos++;
        }else
            set.push_back(make_pair(x,stod(str.substr(last_pos))));
    }
}*/
void
Trainning_Set::insert(const string& str){
    vector<double> x;
    x.push_back(1.0);
    string::size_type pos,last_pos;
    last_pos=pos=0;
    while(pos!=string::npos){
        //last_pos=pos;
        pos=str.find(',',last_pos);
        if(pos!=string::npos) {
            x.push_back(stod(str.substr(last_pos,pos)));
            last_pos=pos;
            ++last_pos;
        }
        else
            set.push_back(make_pair(x,stod(str.substr(last_pos))));
    }
}

double
Trainning_Set::get_x(int ex,int pos) const{
    if(bound_check(ex,set.size()))
        if(bound_check(pos,set[ex].first.size()))
            return set[ex].first[pos];
    return 0.0;
}

double
Trainning_Set::get_y(int pos) const{
    if(bound_check(pos,set.size()))
        return set[pos].second;
    return 0.0;
}

const vector<double>&
Trainning_Set::get_x(int ex) const{
    return set[ex].first;
}

void
Trainning_Set::normalize(){
    norm.clear();
    for(unsigned i=1;i<=dim;++i)
        normalize_x(i);
    normalize_y();
}

/*
void
Trainning_Set::normalize_x(int x){
    double max,min,avg,range;
    max=min=avg=0.0;
    for(unsigned i=0;i<set.size();++i){
        if(max<set[i].first[x])
            max=set[i].first[x];
        if(min>set[i].first[x])
            min=set[i].first[x];
        avg+=set[i].first[x];
    }
    avg=avg/set.size();
    range=max-min;

    for(unsigned i=0;i<set.size();++i){
        set[i].first[x]=(set[i].first[x]-avg)/range;
    }
}
void
Trainning_Set::normalize_y(){
    double max,min,avg,range;
    max=min=avg=0.0;
    for(unsigned i=0;i<set.size();++i){
        if(max<set[i].second)
            max=set[i].second;
        if(min>set[i].second)
            min=set[i].second;
        avg+=set[i].second;
    }
    avg=avg/set.size();
    range=max-min;

    for(unsigned i=0;i<set.size();++i){
        set[i].second=(set[i].second-avg)/range;
    }
}
*/
void
Trainning_Set::normalize_x(int x){
    double max,min,avg,range,elem;
    avg=0.0;
    
    //max=min=avg=0.0;
    //(set.size()>0)
    //? max=min=0.0
    //: max=min=set[0].first[x];
    if (set.size()>0)
        max=min=set[0].second;
    else
        return;

    for(unsigned i=0;i<set.size();++i){
        elem = set[i].first[x];
        if(max<elem)
            max=elem;
        else if(min>elem)
            min=elem;
        avg+=elem;
    }
    avg=avg/set.size();
    range=max-min;
    norm.push_back(make_pair(avg,range));
    //norm[x].first  = avg=avg/set.size();
    //norm[x].second = range=max-min;

    for(unsigned i=0;i<set.size();++i){ //Normalization.
        set[i].first[x]=(set[i].first[x]-avg)/range;
    }
}


void
Trainning_Set::normalize_y(){
    double max,min,avg,range,elem;
    avg=0.0;
    //max=min=avg=0.0;
    //(set.size()>0)
    //? max=min=0.0
    //: max=min=set[0].second;
    if (set.size()>0)
        max=min=set[0].second;
    else
        return;

    for(unsigned i=0;i<set.size();++i){
        elem = set[i].second;
        if(max<elem)
            max=elem;
        if(min>elem)
            min=elem;
        avg+=elem;
    }
    avg=avg/set.size();
    range=max-min;
    norm.push_back(make_pair(avg,range));
    //norm[dim +1].first  = avg=avg/set.size();
    //norm[dim +1].second = range=max-min;

    for(unsigned i=0;i<set.size();++i){
        set[i].second=(set[i].second-avg)/range;
    }
}

Regression::Regression(){
    dim=0;
    theta=new double;
    theta_aux=new double;
    alpha=1.0;
}

Regression::Regression(int dimensions,double alpha){
    if(dimensions<1){
        cerr << "Error: cannot create Regression of <1 dimensions" << endl;
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

Regression::Regression(const Regression& reg){
    Copy(reg);
}

Regression::~Regression(){
    dim=0;
    alpha=0.0;
    if(theta!=NULL)
        delete [] theta;
    if(theta_aux!=NULL)
        delete [] theta_aux;
}

Regression& Regression::operator=(const Regression& reg){
    if(this!=&reg){
        (*this).~Regression();
        Copy(reg);
    }
    return *this;
}

void
Regression::Copy(const Regression& reg){
    dim=reg.dim;
    theta=new double[dim+1];
    theta_aux=new double[dim+1];
    for(unsigned i=0;i<=dim;++i)
        theta[i]=reg.theta[i];
}

double
Regression::convergence()const{
    double conv=0.0;
    for(unsigned i=0;i<=dim;++i)
        conv+=abs(theta[i]-theta_aux[i]);
    return conv;
}

double
Regression::evaluate(const vector<double>& x)const{
    double y=theta[0];
    for(unsigned i=1;i<=dim;++i)
        y+=theta[i]*x[i];
    return y;
}

void
Regression::gradient_descent(const Trainning_Set& train_set){
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
                    file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "+";
                    //file << theta[i] << "+";
                else if(i==dim)
                    //file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "*x, ";
                    file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "*x, ";
                    //file << theta[i] << "*x, ";
                else
                    //file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "*x+";
                    file << (theta[i]*trainAux.norm[i].second)+trainAux.norm[i].first << "*x+";
                    //file << theta[i] << "*x+";
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


void printMatrix(boost::numeric::ublas::matrix<double> matrix) {
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
Regression::normal_equation(const Trainning_Set& train_set){
	boost::numeric::ublas::matrix<double> X (train_set.size(),train_set.get_dim()+1);
	boost::numeric::ublas::matrix<double> X_t (train_set.get_dim()+1,train_set.size());
	boost::numeric::ublas::vector<double> y (train_set.size());

	// Obtaining X and transpose of X
	for(unsigned i=0; i < train_set.size(); ++i){
		for(unsigned j=0; j <= train_set.get_dim(); ++j){
			X(i,j) = train_set.get_x(i,j);
			X_t(j,i) = train_set.get_x(i,j);
		}
        y(i) = train_set.get_y(i);
	}
	// X = X · X^t
	X=boost::numeric::ublas::prod(X_t,X);

    // A = X^-1
    boost::numeric::ublas::matrix<double> A(X.size1(),X.size2());
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
            file << theta[i] << "*x, ";
        else
            file << theta[i] << "*x+";
    }
    /* Prueba funcion inverse
	boost::numeric::ublas::matrix<double> aux2(4,4),aux3(4,4);
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
Regression::inverse(const boost::numeric::ublas::matrix<double>& mat,
                    boost::numeric::ublas::matrix<double>& inverse)const{

    using namespace boost::numeric::ublas;
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
