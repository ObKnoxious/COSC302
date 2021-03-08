#ifndef __PPM_H__
#define __PPM_H__

//#include <>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
struct RGB { 
	RGB() {
		R =0;
		G =0;
		B =0;
	}
	RGB(unsigned char ir, unsigned char ig, unsigned char ib){
		R=ir;
		G=ig;
		B=ib;
	}
	unsigned char R, G, B;
};


class PPM { 
	public:
		//PPM();
		~PPM() {};
		//PPM(unsigned char h, unsigned char rw, unsigned char cl, unsigned char mx);

		void read(string fn);
		void write(string fn);

		RGB *operator[](int) {}

		int get_Nrows() {
			return rows;	
		}
		int get_Ncols() {
			return columns;
		}

	private:
		string head;
		int rows;
		int columns;
		int maxi;

		RGB **img;
};

//PPM::PPM() {	
	//*img = new RGB();
	//rows = 0;
	//columns = 0;
	//maxi = 0;
//}

//PPM::PPM(unsigned char h, unsigned char rw, unsigned char cl, unsigned char mx){
	//head = h;
	//rows = rw;
	//columns = cl;
	//maxi = mx;
	//[>*img = new RGB();

//}
void PPM::read(string fn) { 
	ifstream fin;
	fin.open(fn.c_str());
	if(!fin.is_open()){
		
		cout << "usage: ./Crypto -encode|decode image.ppm\n";
		exit(0);	
	}
	string h;
	//unsigned char rw;
	//unsigned char cl;
	//unsigned char mx;
	int rw;
	int cl;
	int mx;
	fin >> h >> cl >> rw >> mx;
	//cout << h << '\t' << rw << '\t' << cl << '\t' << mx << '\n';
	if(h != "P6"){
		
		cout << "File not of P6 type\n";
		exit(0);
	}else if(cl < 1 || rw < 1){
		cout << "File has invalid dimmensions\n";
	}else if(mx > 255){
		cout << "File max intensity too great\n";
	}
	head =h;
	rows =rw;
	columns =cl;
	maxi = mx;
	fin.get();
	while(fin.peek() == '\n'){
		fin.get();
	}
	img = new RGB*[rows];
	for(int i=0; i< rows; i++){
		img[i] = new RGB[columns];
	}
	size_t size = 3 * rw * cl;
	char * buffer = new char[size];
	fin.read(buffer, size);
	for(int i =0; i<rows; i++){
		for(int j =0; j<columns; j++){
			img[i][j].R = buffer[(i*rw*3) + 3 * j];
			img[i][j].G = buffer[(i*rw*3) + 3 * j +1];
			img[i][j].B = buffer[(i*rw*3) + 3 * j +2];
		}
	}
	delete[] buffer;
	fin.close();
	
}

void PPM::write(string fn) { 
	ofstream fout;
	fn.insert(fn.size()-4, "_wsmg");
	fout.open(fn.c_str());
	if(!(fout.is_open())){
		cout << "File could not be opened\n";
		exit(0);
	}
	fout << "P6\n" << columns << ' ' << rows << ' ' << '\n' << maxi << '\n';

	for(int i =0; i<rows; i++){
		for(int j =0; j<columns; j++){
			fout.write((char *)&img[i][j].R, 1);
			fout.write((char *)&img[i][j].G, 1);
			fout.write((char *)&img[i][j].B, 1);
		}
	}

}
#endif
