CFLAGS = -Wall -g
CC = gcc
LIBS = -lm -lmatheval
OBJ = main.o newton.o mathLib.o utils.o methods.o

all: newtonSNL

newtonSNL: $(OBJ)
	$(CC) -o newtonSNL $(OBJ) $(LIBS)

run: all
	./newtonSNL 

valgrind: all
	valgrind ./newtonSNL

valgrindFull: all
	valgrind --leak-check=full --show-leak-kinds=all ./newtonSNL

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

newton.o: newton.c newton.h
	$(CC) -c newton.c $(CFLAGS)

mathLib.o: mathLib.c mathLib.h
	$(CC) -c mathLib.c $(CFLAGS)

utils.o: utils.c utils.h
	$(CC) -c utils.c $(CFLAGS)

methods.o: methods.c methods.h
	$(CC) -c methods.c $(CFLAGS)

clean:
	$(RM) *.o

purge: clean
	$(RM) newtonSNL