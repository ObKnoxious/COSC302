#include <string>
#include <vector>
using namespace std;

#include "PPM.h"
//#include "Rnumgen.h"
//#include "PPM.cpp"

const char ETX = 0x3;

struct pixel {
	int x;
	int y;
};

void set_pixel_list(PPM &img, vector<pixel> &spl) {
	//int size = img.get_Nrows() * img.get_Ncols();
	for(int i=0; i < img.get_Nrows(); i+=2){
		for(int j=0; j< img.get_Ncols(); j+=2){
			pixel t;
			t.x=j;
			t.y=i;
			spl.push_back(t);
		}
	}
		
}


void encode(PPM &img, vector<pixel> spl) {
	int p = 0;
	char e;
	while(cin.get(e)){
		for(int i = 0; i < 7; i++){
			if(p % 3 == 0){
				img[spl[p].y][spl[p].x].R &= 0xFE;
				img[spl[p].y][spl[p].x].R |= (e & 0x01);
		
			}
			if(p % 3 == 1){
				img[spl[p].y][spl[p].x].G &= 0xFE;
				img[spl[p].y][spl[p].x].G |= (e & 0x01);
			}
			if(p % 3 == 2){
				img[spl[p].y][spl[p].x].B &= 0xFE;
				img[spl[p].y][spl[p].x].B |= (e & 0x01);
			}
			e>>=1;
			p++;

		}
		
	}
	for(int i = 0; i < 7; i++){
		if(p % 3 == 0){
			img[spl[p].y][spl[p].x].R &= 0xFE;
			img[spl[p].y][spl[p].x].R |= (ETX>>i & 0x01);
	
		}
		if(p % 3 == 1){
			img[spl[p].y][spl[p].x].G &= 0xFE;
			img[spl[p].y][spl[p].x].G |= (ETX>>i & 0x01);
		}
		if(p % 3 == 2){
			img[spl[p].y][spl[p].x].B &= 0xFE;
			img[spl[p].y][spl[p].x].B |= (ETX>>i & 0x01);
		}
		
		p++;
	}
	
}

void decode(PPM &img, vector<pixel> spl) {
	int p =0;
	char c=0x0;
	while(true){
		for(int i =0; i< 7; i++){
			if(p % 3 == 0){
				c |= (img[spl[p].y][spl[p].x].R & 0x1) <<i;
			}else if(p % 3 == 1){
				c |= (img[spl[p].y][spl[p].x].G & 0x1) << i;
			}else{
				c |= (img[spl[p].y][spl[p].x].B & 0x1) << i;
			}
			p++;
		}
		if(c == ETX){
			break;
		}
		cout << c;
		c = 0x0;

	}

}

int main(int argc, char *argv[]) {
	//parse command line arguments
		//if something not right,
			//print error message and exit


			//PPM img;
	if(argc < 3 || argc > 6){
		cout << "usage: ./Crypto -encode|decode image.ppm\n";
		return 1;
	}
	string fname = string(argv[argc-1]);
	PPM img;	
	img.read(fname);
	vector<pixel> spl;
	set_pixel_list(img, spl);
	img.write(fname);	
	//declare pixel_list

		//set_pixel_list(pixel_list);

	//if (mode = ENCODE) {
	if(string(argv[1]) == "-encode"){
		encode(img, spl);
		img.write(fname);
		return 0;
	
	}
	if(string(argv[1]) == "-decode"){
		decode(img, spl);
		img.write(fname);
		return 0;
	
	}
		//img.write(fname)
	//}
	//else if (mode = DECODE){ 
		//decode(img, pixel_list);
	//}
//
}
