// Knox Crichton Lab 2
#include <iostream>
#include <string>
#include <fstream>

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
	in >> fname >> lname >> num;
}

ostream & operator<<(ostream &out, const data &r){
	//TODO
}


void printlist(
