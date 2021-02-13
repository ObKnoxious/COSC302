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
	in >> r.fname >> r.lname >> r.num;
	//in >> r.lname;
	//in >> r.num;
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

//int partition(vector<data> &v, int l, int h){
	//data pivot = v[h];
	//int i = (l-1);
	//for(int j = l; j <= h -1; j++){
		//if(v[j] < pivot){
			//i++;
			//swap(v[i], v[j]);
		//}
	//}
	//swap(v[i+1], v[h]);
	//return (i+1);
//}

void quickselect(vector<data> &v,int left, int k,  int right){
	//left =0;
	//right = v.size()-1;
	//while(right>left){
		//swap(v[int(rand() % (right-left) + left)], v[right]);
		//data pivot = v[right];
		
		//int i = (left-1);
		//for(int j = left; j <= right -1; j++){
			//if(v[j] < pivot){
				//i++;
				//swap(v[i], v[j]);
			//}
		//}
		//swap(v[i+1], v[right]);
		//int pindex = i+1;
		//if(pindex == k){
			//return;
		//}
		//if(k < pindex){
			//right = pindex-1;
		//}else{
			//left=pindex+1;
		//}
	//}
	while(left < right){
		int n = right -left;
		int pindex = left + rand() % n;
		//cout << "left " << left << " right " << right  << " pindex " << pindex << "\n";
		data pivot = v[pindex];
		swap(v[pindex], v[right]);
		//int pindex = left + rand() & (right -left);
		//
		//data pivot = v[pindex];
		//swap(v[pindex], v[right]);
		int i = left;
		int j = right-1;
		while(true){
			while(v[i] < pivot){
				i++;
			}
			while(pivot < v[j]){
				j--;
				if(j<=0){
					break;
				}
			}
			if(i>=j){
				break;
			}
			swap(v[i],v[j]);
		}
		pindex=i;
		swap(v[pindex], v[right]);
		if(pindex == k){
			return;
		}
		if(k < pindex){
			right = pindex -1;
		}else{
			left = pindex+1;
		}
		
	}
	
}

void quicksort(vector<data> &v, int l, int h){
	if(l<h){
	//cout << "Great news, you are inside quicksort!\n";
		swap(v[int(rand() % (h-l) + l)], v[h]);
		data pivot = v[h];
		
		int i = (l-1);
		for(int j = l; j <= h -1; j++){
			if(v[j] < pivot){
				i++;
				swap(v[i], v[j]);
			}
		}
		swap(v[i+1], v[h]);
		int pindex = i+1;
		quicksort(v, l, pindex-1);
		quicksort(v, pindex+1, h);
	}
}




int main(int argc, char *argv[]){
	//cout << argv[1];
	vector<string> io{"-stl", "-rpivot"};
	if(argc > 2 && find(io.begin(), io.end(), string(argv[1])) != io.end()){
		//cout << "Args valid\n";
		ifstream fin;
		fin.open(argv[argc-1]);
		//string ifn, iln, ipn;
		vector<data> h;
		//while(fin >> ifn >> iln >> ipn){
			//data d = data(ifn, iln, ipn);
			////cout << d;
			//h.push_back(d);
		//}
		data d;
		while(fin >> d){
			h.push_back(d);	
		}
		fin.close();
		if(string(argv[1]) == "-stl"){
			sort(h.begin(), h.end());
		}else if(string(argv[1]) == "-rpivot" && argc != 5){
			//cout << "Congrats sailor you used Rpivot!\n";
			quicksort(h, 0, h.size()-1);
		}else if(argc == 5 && string(argv[1]) == "-rpivot"){
			//quicksort(h, 0, h.size()-1);
			int ko = atoi(argv[2]);
			int kone = atoi(argv[3]);
			if(ko < 0){
				ko = 0;
			}
			if(kone > h.size()-1){
				kone = h.size()-1;
			}
			quickselect(h, 0, ko, h.size()-1);
			quickselect(h, ko, kone, h.size()-1);
			quicksort(h, ko, kone);

		}
		printlist(h);
	}else{
		cerr << "usage: ./Qsort -stl | -rpivot [k0 k1] file.txt\n";
	}

}
