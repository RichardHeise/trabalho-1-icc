#  Makefile
#  06/04/2022
#  Gabriel Lüders (GRR20190172)
#  Richard Fernando Heise Ferreira (GRR20191053) 

# ----------------------------------------------------------------- #
# Declaration of targets and compiling options
CFLAGS = -Wall -g -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -O3 -mavx -march=native
CC = gcc
LIBS = -lm -lmatheval -L${LIKWID_LIB} -llikwid
OBJ = main.o newton.o mathLib.o utils.o methods.o rosenbrock.o
INPUT = entrada.dat

# ----------------------------------------------------------------- #
# Compilation directives
all: newtonPC

newtonPC: $(OBJ)
	$(CC) -o newtonPC $(OBJ) $(LIBS)

run: all
	likwid-perfctr -C 3 -g L3 -O -m ./newtonPC < $(INPUT)

runL3: all
	likwid-perfctr -C 3 -g L3 -O -m ./newtonPC < $(INPUT)

runL2: all
	likwid-perfctr -C 3 -g L2CACHE -O -m ./newtonPC < $(INPUT)

runFLOPS_DP: all
	likwid-perfctr -C 3 -g FLOPS_DP -O -m ./newtonPC < $(INPUT)

runFLOPS_AVX: all
	likwid-perfctr -C 3 -g FLOPS_AVX -O -m ./newtonPC < $(INPUT)

runOutput: all
	./newtonPC < $(INPUT) -o saida.txt

valgrind: all
	valgrind ./newtonPC < $(INPUT)

valgrindFull: all
	valgrind --leak-check=full --show-leak-kinds=all  ./newtonPC < $(INPUT)

valgrindDoubleFree: all
	valgrind --track-origins=yes --keep-stacktraces=alloc-and-free --error-limit=no --num-callers=40 ./newtonPC < $(INPUT)

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

rosenbrock.o: rosenbrock.c rosenbrock.h
	$(CC) -c rosenbrock.c $(CFLAGS)

# ----------------------------------------------------------------- #
# Cleaning directives
clean:
	$(RM) *.o

purge: clean
	$(RM) newtonPC