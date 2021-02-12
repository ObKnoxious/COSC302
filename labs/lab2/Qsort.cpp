// Knox Crichton Lab 2
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class data{
	public:
		friend istream & operator>>(istream &, data &);
		friend ostream & operator<<(ostream &, const data &);

	private:
		string fname;
		string lname;
		string num;
};

istream & operator>>(istream &in, data &r){
	in >> r.fname >> r.lname >> r.num;
}

ostream & operator<<(ostream &out, const data &r){
	//TODO
}


void printlist(vector<data> v){
	for(int i =0; i < v.end(), i++){
	}
};

int main(inr argc, char *argv[]){
	ifstream fin;
	fin.open(argv[2]);

}

