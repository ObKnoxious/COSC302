#include <...>
using namespace std;

#include "PPM.h"
#include "Rnumgen.h"

const char ETX = 0x3;

struct pixel {
  write this
}

void set_pixel_list(...) {
  write this
}

void encode(...) {
  write this
}

void decode(...) {
  write this
}

int main(int argc, char *argv[]) {
  parse command line arguments
  if something not right,
    print error message and exit

  PPM img;
  img.read(fname);

  declare pixel_list

  set_pixel_list(pixel_list);

  if (mode = ENCODE) {
    encode(img, pixel_list);
	img.write(fname)
  }
  else
  if (mode = DECODE) 
    decode(img, pixel_list);
}
