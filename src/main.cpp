#include "linearRegression.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void insertExample(string& s,list<Regression::Example >& l){
	double* x=new double[1];
	x[0]=stod(s.substr(0,s.find(',')));
	double y=stod(s.substr(s.find(',')+1));

	l.push_back(make_pair(x,y));
}

int
main(int argc,char** argv){
	Regression reg(3,0.1);
	cout << reg;

	ifstream f;
	f.open(argv[1]);
	if(!f){
		cerr << "Error: no se pudo abrir el archivo." << endl;
		return 0;
	}

	string read;
	list<Regression::Example > list;
	unsigned x=0;
	while(!f.eof()){
		getline(f,read);
		if(!read.empty())
			insertExample(read,list);
	}

	for(Regression::Example ex: list)
		cout << ex.first[0] << "," << ex.second << endl;

	return 1;
}
