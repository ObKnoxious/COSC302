// Lab 1, COSC302
// By Knox Crichton
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
using namespace std;

struct fruit{
	string name;
	float quant;
	float cost;
	fruit(string f, float q, float c){
		name = f;
		quant = q;
		cost = c;
	}
	bool operator <(const fruit& f) const{
		this->name < f.name;
		//return lexicographical_compare(name.c_str(), name.c_str()+int(strlen(name.c_str())), f.name.c_str(), f.name.c_str()+strlen(name.c_str()));
	}
               //fruit operator +(const fruit& f){
		//if(name != f.name){
			//cerr << "Not the same fruits!";
			//return 1;
		//}else{
			//fruit n = fruit(name, quant+f.qua
};
int main(int argc, char *argv[]){
	vector<string> io;
	io.push_back("-inorder");io.push_back("-sortall");io.push_back("-sortone");
	if(argc == 3 && find(io.begin(), io.end(), string(argv[1])) != io.end()){
		//cout << "In the if\n";
		ifstream f;
		f.open(argv[2]);
		string line;
		//vector<string> lines;
		vector<fruit> flist;
		while(getline(f, line)){
			istringstream iss(line);
			string fr;
			float p, q;
			iss >> fr >> q >> p;
			fruit inF = fruit(fr, q, p);
			flist.push_back(inF);
		}
		//cout << "File read complete\n";
		if(string(argv[1]) == "-sortall"){
			stable_sort(flist.begin(), flist.end());
		}
		if(string(argv[1]) == "-sortone"){
			stable_sort(flist.begin(), flist.end());
			vector<fruit> nlist;
			nlist.push_back(flist.at(0));
			int nt=0;
			for(int i =0; i < flist.size(); i++){
				if(i < flist.size() -1){
					//cout << "i " <<  i << "\n";
					if(flist.at(i).name != flist.at(i+1).name){
						//cout << "Second if\n";
						nlist.push_back(flist.at(i+1));
						nt++;
					}else{
						float qp = flist.at(i+1).quant;
						nlist.at(nt).quant = nlist.at(nt).quant + qp;		
					}
				}
			}

			float tc;
			for(int i = 0; i < nlist.size(); i++){
				float uc = nlist.at(i).quant * nlist.at(i).cost;
				tc+=uc;
				cout << fixed << showpoint << setprecision(2) << setw(20) << setfill('.') <<  left <<  nlist.at(i).name << setfill(' ') <<  setw(6) << right << nlist.at(i).quant <<  " x " <<
					setw(4)  <<  nlist.at(i).cost << " = " <<  setw(7) << right <<  uc << "  : " <<  setw(8) << right << tc << "\n";
			}
		return 0;
		}	
	
			//for(int i = 0; i < flist.size(); i++){
				//int j =1;
				//while(flist.at(i+j).name == flist.at(i).name){
					//flist.at(i).quant+=flist.at(i+j).quant;
					//flist.at(i+j).quant=0;
					//j++;
				//}
			//}
			//cout <<"sortone detected\n";
			//for(int i =0; i < flist.size(); i++){
				//cout << "First for loop i == " << i << "\n";
				//if(flist.at(i).quant != 0){
					//for(int j=0; j < flist.size(); j++){
						//cout << "second for loop j == " << j << "\n";
						//if(flist.at(i).name == flist.at(j).name && flist.at(j).quant != 0){
							//flist.at(i).quant+=flist.at(j).quant;
							//flist.at(j).quant=0;
						//}
					//}
				//}
			//}
			//int e = flist.size();
			//for(int i =0; i<e;i++){
				//if(flist.at(i).quant=0){
					//flist.erase(flist.begin()+i);
					//e--;
				//}
			//}
			//int i =0;
			//cout <<"before while loop\n";
			//while(i < e){
				//cout << "in the while loop\n";
				//if(flist.at(i).quant==0){
					//cout << flist.at(i).name << "\n";
					//flist.erase(flist.begin()+i);
					//e--;
				//}
				//i++;
			//}
		//}
		float tc;
		for(int i = 0; i < flist.size(); i++){
			float uc = flist.at(i).quant * flist.at(i).cost;
			tc+=uc;
			cout << fixed << showpoint << setprecision(2) << setw(20) << setfill('.') <<  left <<  flist.at(i).name << setfill(' ') <<  setw(6) << right << flist.at(i).quant <<  " x " <<
			      	setw(4)  <<  flist.at(i).cost << " = " <<  setw(7) << right <<  uc << "  : " <<  setw(8) << right << tc << "\n";
			
	
		}
	}else{
		cerr << "usage: ./sfruit2 -inorder|sortall|sortone file.txt";
	}
	return 0;	
}

