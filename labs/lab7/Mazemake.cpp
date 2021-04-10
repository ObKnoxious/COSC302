
#include <cstdlib>
#include <ctime>
#include <cstdio>

#include "dset.h"

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

//void swap(cell &c1, cell &c2) { ... }
void swap(cell &c1, cell &c2){
	cell t = c1;
	c1 = c2;
	c2 = t;
}

void randperm( cell(*a)[2], int aS){
	for(int i=aS-1; i>0; --i){
		int t = rand() % (i+1);
		swap(a[i][0], a[t][0]);
		swap(a[i][1], a[t][1]);
	}
}




int main(int argc, char *argv[]) {
	srand(time(NULL));
	if (argc != 4) {
	//print usage error message to stderr
		printf("usage: ./Mazemake nrow ncol maze.txt\n");
		return 0;
	}

  //int Nrow = atoi(argv[1]);
  //int Ncol = atoi(argv[2]);
	int Nrow =atoi(argv[1]);
	int Ncol = atoi(argv[1]);

  //// Grid wall:     (i0,j0) | (i1,j1)
  //// Horizontal wall: (i,j) | (i+1,j)
  //// Vertical wall:   (i,j) | (i,j+1)

  //int N = number of interior grid walls
  	int N = ((Ncol-1)*Nrow) + ((Nrow-1)*Ncol);
	cell wall[N][2];


	int k=0;
  //populate wall[][] with interior grid walls
	for(int i=0; i < Ncol-1; i++){
		for(int j=0; j < Nrow; j++){
			wall[k][0] = cell(i,j);
			wall[k][1] = cell(i+1,j);
			k++;
		}
	}
	for(int i=0; i<Ncol; i++){
		for(int j=0; j< Nrow-1; j++){
			wall[k][0] = cell(i,j);
			wall[k][1] = cell(i,j+1);
			k++;
		}
	}
  //randomly perturb list order: swap based
  //open output file for writing (argv[3])
	//dset ds = dset(Nrow*Ncol);
  //write MAZE, Nrow, Ncol header 

	FILE *fout = fopen(argv[3], "w");
	fprintf(fout, "MAZE %d %d\n", Nrow, Ncol);
	for(int i =0; i<N; i++){
		fprintf(fout, "%3d %3d %3d %3d\n", wall[i][0].x, wall[i][0].y, wall[i][1].x, wall[i][1].y);

	}
	randperm(wall, N);
	FILE *fout2 = fopen("nonrand.txt", "w");
	fprintf(fout2, "MAZE %d %d\n", Nrow, Ncol);
	for(int i =0; i<N; i++){
		fprintf(fout2, "%3d %3d %3d %3d\n", wall[i][0].x, wall[i][0].y, wall[i][1].x, wall[i][1].y);

	}

	
	

  //for (k=0; k<N; k++) {
    //if: pair of cells given by wall[k][] are not
	//connected (belong to different disjoint sets),
	//merge them
	
	//else: write wall location to file as two pairs 
	//of cell indices: i0 j0 i1 j1

    //if: all cells belong to the same set, break
  //}

  //write any remaining walls to file

  //close output file
}
