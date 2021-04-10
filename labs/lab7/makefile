
cc= g++
CFLAGS= -g -Wall
BIN = Mazemake

all: $(BIN)

Mazemake: Mazemake.cpp dset.h dset.cpp
	$(CC) $(CFLAGS) -o Mazemake Mazemake.cpp

clean:
	&rm -f $(BIN)
