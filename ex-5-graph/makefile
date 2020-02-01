CC=gcc
CFLAGS=-O3
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXE=$(OBJ:.o=.x)

all:$(EXE)

$(EXE):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

$(OBJ):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

.PHONY: clean

clean:
	rm $(OBJ) $(EXE)