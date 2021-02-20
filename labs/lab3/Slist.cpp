// include header file(s) needed
using namespace std;
#include <fstream>
#include "Slist.h"
#include <vector>
#include <algorithm>
#include <iomanip>
// modify the data class and the associated input 
// and output operators to store, set and print a 
// line number identifier called ID


class data{
	public:
		friend istream & operator>>(istream &, data &);
		friend ostream & operator<<(ostream &, const data &);
		data(){};
		data(string fn, string ln, string nm);
		bool operator <(const data& d) const{
			if(this->lname == d.lname){
				if(this->fname == d.fname){
					return this->num < d.num;
				}
				return this->fname < d.fname;
			}
			return lname < d.lname;
		};
		void setOrder(int o){
			order =o;
		}
	private:
		string fname;
		string lname;
		int order;
		string num;
};
data::data(string fn, string ln, string nm){
	fname = fn;
	lname = ln;
	num = nm;
};
istream & operator>>(istream &in, data &r){
	in >> r.fname >> r.lname >> r.num;	//in >> r.lname;
	//in >> r.lname;
	//in >> r.num;
	return in;
}


ostream & operator<<(ostream &out, const data &r){
	out << " " << r.lname <<" " << r.fname;
	int l = 25 - (r.fname.length() + r.lname.length() +2);
	for (int i = 0; i < l; i++){
		out << " ";
	}
	out << r.num << setw(9) << right <<r.order << "\n";
	return out;
};

template <typename T>
void printlist(T begin, T end){
	//cout << "In print list\n";
	for(T b = begin; b != end; ++b){
		cout << *b;
	}
}

int main(int argc, char *argv[]) {
  // copy command-line check from Qsort.cpp,
  // then modify to apply to this assignment
	vector<string> io{"-mergesort", "-quicksort"};
	if(argc > 2 && find(io.begin(), io.end(), string(argv[1])) != io.end()){
		// open input file

		ifstream fin;
		fin.open(argv[argc-1]);
		slist<data> A;
		data din;
		int c =1;
		while (fin >> din){
			//cout << "Successfully Reading file\n";
			din.setOrder(c);
			c++;
			A.push_back(din);
		}

		fin.close();
		if(string(argv[1]) == "-mergesort"){
			A.sort("m");
		}else if(string(argv[1]) == "-quicksort"){
			A.sort("q");
		}
		printlist(A.begin(), A.end());
	}else{
		cerr << "usage: ./Slist -mergesort|quicksort|qsort_r3 file.txt\n";
	}
}
