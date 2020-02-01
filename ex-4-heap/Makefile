CC=gcc
CFLAGS=-O3
SRC=$(wildcard *.c)
# OBJ=$(SRC:.c=.o)
EXE=binaryHeap.x

all:$(EXE)

$(EXE):$(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) -I.

# $(OBJ):$(SRC)
# 	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

.PHONY: clean

clean:
	rm $(OBJ) $(EXE)