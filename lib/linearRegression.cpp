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

void
Trainning_Set::insert(const string& str){
	vector<double> x;
	x.push_back(1.0);
	string::size_type pos,last_pos;
	pos=0;
	while(pos!=string::npos){
		last_pos=pos;
		pos=str.find(',',last_pos+1);
		if(pos!=string::npos)
			x.push_back(stod(str.substr(last_pos,pos)));
		else
			set.push_back(make_pair(x,stod(str.substr(last_pos+1))));
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
	for(unsigned i=1;i<=dim;++i)
		normalize_x(i);
	normalize_y();
}

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

Regression::Regression()
{
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

	do{
		for(i=0;i<=dim;++i)
			temp[i]=0;

		// Recorrer vector temp
		for(unsigned j=0;j<=dim;++j)
			// Recorrer vector ejemplos
			for(i=0;i<train_set.size();++i)
				// temp_j = temp_j + (h(x_i) - y_i) * x_i
				temp[j] += (evaluate(train_set.get_x(i)) - train_set.get_y(i)) *train_set.get_x(i,j);
		
		for(i=0;i<=dim;++i){
			// Copy last values of theta for convergence
			theta_aux[i]=theta[i];
			// theta_i = theta_i - 1/m * alpha *temp_i
			theta[i] -= alphaDivNum*temp[i];
			if(k%10==0){
				if(i==0)
					file << theta[i] << "+";
				else if(i==dim)
					file << theta[i] << "*x, ";
				else
					file << theta[i] << "*x+";
			}
		}
		//if(k%100==0)
		//	file << endl;
		k++;
	}while(k<maxIter && (convergence() > minConv*dim));

	cout << k << endl;
	file.close();
	delete [] temp;
}
