
CC = g++
CFLAGS = -Wall -g
BIN = Fruit1 Fruit2 
OBJ = $(BIN:%=%.o)

all: $(BIN)

.cpp: 
	$(CC) $(CFLAGS) -o $* $<

clean:
	@rm -f $(BIN) $(OBJ)
