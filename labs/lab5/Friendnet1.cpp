//#include <...>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void set_oldfriends(vector <string> &name, vector<vector<string> > &friends, int M0, int M1) {
  int N = (int)name.size();
  //initialize 2D-vector-array friends (hint: use vector::assign())

  for (int i=0; i<N; i++) {
	//declare std::set called doknow
	set<string> doknow;
	//initialize M (random number of friends: function of M0, M1)
	int M = (rand() % M1) + M0;
	while ((int)doknow.size() < M) {
	  //compute j (random friend index: hint j != i)
	  if(M != i){
		doknow.insert(name.at(M);
	  }
	  //doknow.insert(j);
	}

	//use iterator to sweep thru doknow set
	//update the corresponding pairs of friends entries
  }
}

//void set_newfriends(2D-vector-array &friends, 2D-vector-array &new_friends) {
  //int N = (int)friends.size();
  //initialize 2D-vector-array new_friends (hint: use vector::assign())

  //for (int i=0; i<N; i++) {
	//for (each adjacent friend: friends[i][j] == 1) {
	  //for (each adjacent friend-of-friend: friends[j][k] == 1) {
	    //if (k-is-not-i && k-is-not-friend-of-i)
	      //update the corresponding pairs of new_friends entries
	  //}
    //}
  //}
//}

//void writetofile(const char *fname, vector<string> &name, 2D-vector-array &friends) {
  //open file

  //int N = (int)name.size();
  //determine max name length

  //for (int i=0; i<N; i++) {
	//for (each adjacent friend: friends[i][j] == 1) {
	  //pretty-print name[i] and name[j] (see assignment) 
  //}

  //close file
//}

int main(int argc, char *argv[]) {
  //parse argc, argv arguments
	if(argc > 1){
		if(string(argv[2]) != "-seed"){
			cerr << "usage: ./friendnet1 [-seed N]\n";
			return 1;
		}
	//print usage message and exit if invalid
	}else{

  //seed random number generator
	srand(time(NULL));
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
  //set_oldfriends(name, friends, M0, M1);
  //writetofile("doknow1.txt", name, friends);

  //set_newfriends(friends, new_friends);
  //writetofile("mightknow1.txt", name, new_friends);

	}
}
