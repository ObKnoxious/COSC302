#include <string>
using namespace std;

#include "PPM.h"
//#include "Rnumgen.h"
//#include "PPM.cpp"

const char ETX = 0x3;

struct pixel {
	//write this
};

//void set_pixel_list(...) {
	////write this
//}

//void encode(...) {
	////write this
//}

//void decode(...) {
	////write this
//}

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
	img.write(fname);	
	//declare pixel_list

		//set_pixel_list(pixel_list);

	//if (mode = ENCODE) {
		//encode(img, pixel_list);
		//img.write(fname)
	//}
	//else if (mode = DECODE){ 
		//decode(img, pixel_list);
	//}
//
}
