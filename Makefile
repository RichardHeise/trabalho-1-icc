CFLAGS = -Wall
CC = gcc
LIBS = -lm -lmatheval
OBJ = main.o newton.o mathSNL.o

all: newtonSNL

newtonSNL: $(OBJ)
	$(CC) -o newtonSNL $(OBJ) $(LIBS)

run: newtonSNL
	./newtonSNL 

main.o:
	$(CC) -c main.c $(CFLAGS)

newton.o:
	$(CC) -c newton.c $(CFLAGS)

mathSNL.o:
	$(CC) -c mathSNL.c $(CFLAGS)

clean:
	$(RM) *.o

purge: clean
	$(RM) newtonSNL