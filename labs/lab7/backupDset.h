#indef __CN_MEMORY__
#define __CN_MEMORY__

#include <stdlib.h>

#define allocate2d(v,t,x,y){
	int _i;
	v = (type **) calloc(x, sizeof(type *));
	for(_i =0; _i < x; _i++){
		v[_i] = (type *) calloc(y, sizeof(type));
	}
}
#define free2d(v, t, x, y) {
	int _i;                     
	for (_i = 0; _i < x; _i++){ 
		free(var[_i]);      
	}
	free(v);  
}

#define free3d(v, t , s, y , z){
	int _i, _j;
	for(_i=0; _i< x; _i++){
		for(_j=0; _j<y; _j++){
			free(v[_i][_j]);
		}
		free(v[_i]);
	}
}
