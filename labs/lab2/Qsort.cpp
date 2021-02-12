// Knox Crichton Lab 2
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class data{
	public:
		friend istream & operator>>(istream &, data &);
		friend ostream & operator<<(ostream &, const data &);
		data(){};
		data(string fn, string ln, string nm);

	private:
		string fname;
		string lname;
		string num;
};

data::data(string fn, string ln, string nm){
	fname = fn;
	lname = ln;
	num = nm;
};

istream & operator>>(istream &in, data &r){
	in >> r.fname;
	in >> r.lname;
	in >> r.num;
	return in;
}


ostream & operator<<(ostream &out, const data &r){
	out << r.fname <<" " << r.lname;
	int l = 24 - (r.fname.length() + r.lname.length() +1);
	for (int i = 0; i < l; i++){
		out << " ";
	}
	out << r.num << "\n";
	return out;
}


void printlist(vector<data> v){
	for(int i =0; i < v.size(), i++;){
		cout << v[i];
	}
};

int main(int argc, char *argv[]){
	vector<string> io{"-stl", "-rpivot"};
	if(argc > 2 && find(io.begin(), io.end(), string(argv[1])) != io.end()){
	//if(argc >= 3 && find(io.begin(), io.end(), string(argv[1])) != io.end()){
		if(string(argv[1]) == "-stl"){
			ifstream fin;
			fin.open(argv[2]);
			string ifn, iln, ipn;
			vector<data> h;
			while(fin >> ifn >> iln >> ipn){
				data d = data(ifn, iln, ipn);
				cout << d;
				h.push_back(d);
			};
			printlist(h);
		}
	}else{
		cerr << "usage: ./Qsort -stl | -rpivot [k0 k1] file.tx\n";
	}
	//ifstream fin;
	//fin.open(argv[1]);
	//data t;
	//vector<data> h;
	//while(fin >> t){
		//h.push_back(t);
	//}
	//printlist(h);

}

