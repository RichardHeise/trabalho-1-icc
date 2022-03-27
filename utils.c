/**
 *  Arquivo com as implementações de funções úteis em geral
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/
 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "utils.h"

void* mallocCheck(int size, char* error){
  void* pointer = malloc(size);
  if(!pointer){
    fprintf(stderr, "Error allocating memory: %s\n", error);
    exit(2);
  }

  return pointer;
}

/* ====================================================================================== */

void** mallocMatrix(int lin, int col, unsigned int varSize){
  void** mat;
  int i;

  mat = mallocCheck(lin * sizeof(void*), "allocating line pointers for matrix");
  mat[0] = mallocCheck(lin * col * varSize, "allocating element vector");

  for(i = 1; i < lin; i++)
    mat[i] = mat[0] + i * col * varSize;

  return mat;
}

/* ====================================================================================== */

void matrixDestructor(void** mat){
  free(mat[0]);
  free(mat);
}

/* ====================================================================================== */

double timestamp(void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return((double)(tp.tv_sec*1.0e3 + tp.tv_nsec*1.0e-6));
}

/* ====================================================================================== */

FILE* openFile(char* path, char* mode){
  FILE* file = fopen(path, mode);
    
  if(!file){
    fprintf(stderr, "Error opening %s\n", path);
    exit(0);
  }

  return file;
}

/* ====================================================================================== */

void parseArgs(int argc, char** argv, const char *args, FILE** valueO){  
  opterr = 0;
  *valueO = stdout;

  int option = getopt(argc, argv, args);

  if(option == -1){
    *valueO = stdout;
    return;
  }

  while(option != -1){
    switch (option){
      case 'o':
        *valueO = openFile(optarg, "w");
        break;
      case 'h':
        fprintf(
          stderr, 
          "This program finds critical points of a function\n"
        );
      default:
        fprintf (
          stderr, 
          "Usage: %s -o <output_file>\n", 
         argv[0]
        );
        exit (1) ;
    }

    option = getopt(argc, argv, args);
  }
}

double norm(double* vector, unsigned int n) {
  double norm = 0.0;
  for (int i = 0; i < n; i++) {
      norm += vector[i]*vector[i];
  }

  return sqrt(norm);
}
