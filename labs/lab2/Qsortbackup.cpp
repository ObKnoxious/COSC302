// Knox Crichton Lab 2
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

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

//bool data::operator <(const data& d) const{
	////if(this->lname == d.lname){
		////if(this->fname == d.fname){
			////return this->num < d.num;
		////}
		////return this->fname < d.fname;
	////}
	//return this->lname < d.lname;
//};

istream & operator>>(istream &in, data &r){
	in >> r.fname;
	in >> r.lname;
	in >> r.num;
	return in;
}


ostream & operator<<(ostream &out, const data &r){
	out << r.lname <<", " << r.fname;
	int l = 24 - (r.fname.length() + r.lname.length() +2);
	for (int i = 0; i < l; i++){
		out << " ";
	}
	out << r.num << "\n";
	return out;
}


void printlist(vector<data> v){
	for(int i =0; i < v.size(); i++){
		cout << v.at(i);
	}
};

//int partition(vector<data> &v, int left, int right){
	//if((right - left +1)<=3){
		//return (left+right)/2;
	//}
	//int pindex = (right+left)/2;
	//data pivot = v[pindex];
	//swap(v[pindex],v[right-1]);
//}

//void quicksort(vector<data> &v, int left, int right){
	//cout << "Good news matey quicksort is recurring!\n";
	//if((right - left +1)<=3){
		//return (left+right)/2;
	//}
	//int pindex = (right+left)/2;
	//data pivot = v[pindex];
	//swap(v[pindex],v[right-1]);
	//quicksort(v, left, pindex-1);
	//quicksort(v, pindex+1, right);
//}

//void quicksort(vector<data> &v, int n){
	//cout << "Aye sailor you called quicksort!\n";
	//quicksort(v, 0, n-1);
//}
//
int partition(vector<data>, int l, int h){
	int pivot = v[h];
	int i = (low-1);
	for(int j = l; j <= h -1; j++){
		if(arr[j] < pivot){
			i++;
			swap(&v[i], &v[j]);
		}
	}
	swap(&v[i+1], &v[h]);
	return (i+1);
}

void quicksort(vector<data> v, int l, int h){
	if(l<h){
		int pindex = partition(v, l, h);
		quicksort(v, l, pindex-1);
		quicksort(v, pindex-1, h);
	}
}




int main(int argc, char *argv[]){
	//cout << argv[1];
	vector<string> io{"-stl", "-rpivot"};
	if(argc > 2 && find(io.begin(), io.end(), string(argv[1])) != io.end()){
		//cout << "Args valid\n";
		ifstream fin;
		fin.open(argv[argc-1]);
		string ifn, iln, ipn;
		vector<data> h;
		while(fin >> ifn >> iln >> ipn){
			data d = data(ifn, iln, ipn);
			//cout << d;
			h.push_back(d);
		}
		if(string(argv[1]) == "-stl"){
			stable_sort(h.begin(), h.end());
		}
		if(string(argv[1]) == "-rpivot"){
			cout << "Congrats sailor you used Rpivot!\n";
			//quicksort(h, (rand() % h.size()));
		}
		printlist(h);
	}else{
		cerr << "usage: ./Qsort -stl | -rpivot [k0 k1] file.txt\n";
	}

}

