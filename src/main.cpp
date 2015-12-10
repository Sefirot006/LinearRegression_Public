#include "linearRegression.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void insertExample(string& s,vector<Regression::Example >& l){
	double* x=new double[2];
	x[0]=1.0;
	x[1]=stod(s.substr(0,s.find(',')));
	double y=stod(s.substr(s.find(',')+1));

	l.push_back(make_pair(x,y));
}

int
main(int argc,char** argv){
	Regression reg(1,0.00000001);
	cout << reg;

	ifstream f;
	f.open(argv[1]);
	if(!f){
		cerr << "Error: no se pudo abrir el archivo." << endl;
		return 0;
	}
	string read;
	vector<Regression::Example > list;
	unsigned x=0;
	while(!f.eof()){
		getline(f,read);
		if(!read.empty())
			insertExample(read,list);
	}
	f.close();
	Trainning_Set train(argv[1],1);

	for(Regression::Example ex: list)
		cout << ex.first[1] << "," << ex.second << endl;

	reg.gradient_descent(list);

	//cout << train;

	return 1;
}
