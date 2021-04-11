#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
//struct cell { ... }
struct cell{
	int x;
	int y;
	cell(){
		x=-1;
		y=-1;
	}
	cell(int i, int j){
		x=i;
		y=j;
	}
};
//int main(int argc, char *argv[]) {
int main(int argc, char *argv[]){
//if (argc != 3) {
	if(argc != 3){
    //print usage error message to stderr
		// Pretty sure write up says we can't use stderr but...
		std::cerr << "Usage error";
	//return 0;
		return 0;
	}
  //} 

  //open input file for reading
  	FILE *fin = fopen(argv[1], "r");
	//char buf[100];
	int Nrow;
	int Ncol;
	fscanf(fin, "MAZE %i %i", &Nrow, &Ncol);
	std::cout << Nrow << " " << Ncol << '\n';

	
  //open output file for writing


  //determine Nrow,Ncol from input file

  //create array of walls for each grid cell
  //initialize to have boundary walls set and
  //interior walls unset

  //bool wall[Nrow][Ncol][4];

  //read input file, set interior walls

  //initalize DFS path computation

  //source = (0,0)
  //sink = (Nrow-1,Ncol-1)

  //bool iswhite[][]
  //cell link[][]

  //carry out DFS source-to-sink computation

  //write PATH, Nrow, Ncol header
  //write cells on path to file

  //close open files
//}
}
