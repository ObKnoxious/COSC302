#ifndef __PPM_H__
#define __PPM_H__

#include <>

struct RGB { 
  RGB() {
  	R =0;
	G =0;
	B =0;
  }

  unsigned char R, G, B;
};

class PPM { 
	public:
		PPM() {	
			**img = new RGB();
		}
		~PPM() {

		}

		void read();
		void write();

		RGB *operator[](int) {}

		int get_Nrows() {}
		int get_Ncols() {}

	private:
		RGB **img;
};

#endif
