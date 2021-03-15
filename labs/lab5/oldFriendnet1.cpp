//#include <...>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <fstream>
#include <iomanip>
using namespace std;

void set_oldfriends(vector <string> &name, vector<vector<string> > &friends, int M0, int M1) {
	int N = (int)name.size();
  //initialize 2D-vector-array friends (hint: use vector::assign())
	//friends.assign(N, " ");
	//for (int i=0; i<N; i++) {
		//declare std::set called doknow
		//set<string> doknow;
		//initialize M (random number of friends: function of M0, M1)
		for(int i =0; i < N; i++){
			//friends.at(i).at(0) == name.at(i);
			
			//cout << "i " << i << '\n';
			vector<string> t;
			t.push_back(name.at(i));
			friends.push_back(t);
			int M = (rand() % M1) + M0;
			for(int j=0; j< M; j++){
				cout << "j " << j << '\n';
				int r = (rand() % ((N-1) - 0 + 1)) + 0;
				//cout << "r " << r << '\n';
				while(r == i){	
					cout << "Random matches i, redoing\n";
					r = (rand() % ((N-1) - 0 + 1)) + 0;
				}
				friends.at(i).push_back(name.at(r));
			}
		}
		//while ((int)doknow.size() < M) {
			//compute j (random friend index: hint j != i)
			//if(M != i){
				//doknow.insert(name.at(M));
			//}
			//doknow.insert(j);
		//}

		//use iterator to sweep thru doknow set
		//update the corresponding pairs of friends entries
	//}
}

void set_newfriends(vector<vector<string> >  &friends, vector<vector<string> > &new_friends) {
	int N = (int)friends.size();
	for(int i=0; i <N; i++){
		vector<string> t;
		t.push_back(friends.at(i).at(0));
		new_friends.push_back(t);
		for(int j=1; j<friends.at(i).size(); j++){
			for(int k=0; k<N; k++){
				if(friends.at(k).at(0) == friends.at(i).at(j)){
					for(int l=1; l< friends.at(k).size(); l++){
						new_friends.at(i).push_back(friends.at(k).at(l));
					}
				}
			}
		}
	}
}
  //for (int i=0; i<N; i++) {
	//for (each adjacent friend: friends[i][j] == 1) {
	  //for (each adjacent friend-of-friend: friends[j][k] == 1) {
	    //if (k-is-not-i && k-is-not-friend-of-i)
	      //update the corresponding pairs of new_friends entries
	  //}
    //}
  //}
//}

void writetofile(const char *fname, vector<string> &name, vector<vector <string> > &friends) {
  //open file
	ofstream fout;
	fout.open(fname);
	int N = (int)name.size();
  //determine max name length

  for (int i=0; i<N; i++) {
	//for (each adjacent friend: friends[i][j] == 1) {
	fout << left << setw(11) << setfill (' ') << friends[i][0] << ": ";
	//cout << friends[i][0] << " : ";
	  for(int j=1; j< friends[i].size(); j++){
		  fout << friends[i][j] << ' ';
		  //cout << friends[i][j] << ' ';
	  //pretty-print name[i] and name[j] (see assignment) 

	}
	  fout << '\n';
	//cout << '\n';
  }
  //close file
	fout.close();
}


int main(int argc, char *argv[]) {
  //parse argc, argv arguments
	if(argc > 1){
		if(string(argv[1]) != "-seed"){
			cerr << "usage: ./Friendnet1 [-seed N]\n";
			return 1;
		}
		int r = atoi(argv[2]);
		srand(r);
	}
//print usage message and exit if invalid

//seed random number generator
	//srand(time(NULL));
	vector<string> name;
	string n;
	while(cin >> n){
		name.push_back(n);
	}
	//read strings from stdin into name vector
	//for(int i =0; i < name.size(); i++){
		//cout << name.at(i) << '\t';
	//}
	int M0 = 1; // min number of friends
	int M1 = 3; // max number of friends

  //declare 2D-vector-array called friends
	vector<vector<string> > friends;
  //declare 2D-vector-array called new_friends
	vector<vector<string> > new_friends;
	set_oldfriends(name, friends, M0, M1);
  	writetofile("doknow1.txt", name, friends);

  	set_newfriends(friends, new_friends);
  	writetofile("mightknow1.txt", name, new_friends);
//
}
