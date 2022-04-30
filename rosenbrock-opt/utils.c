/**
 *  This file contains the implementations of useful functions in general
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/
 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <likwid.h>
#include "utils.h"

void* mallocCheck(int size, char* error){
  void* pointer = malloc(size);
  if(!pointer){
    fprintf(stderr, "Error allocating memory: %s\n", error);
    exit(MEM_ALLOC_ERROR);
  }

  return pointer;
}

void checkZeroDivision(double denominator, char* funcName, char* cFunction){
  if(denominator == 0){
    fprintf(stderr, "There has been a try to divide by zero while resolving function %s\n", funcName);
    fprintf(stderr, "Error at %s\n", cFunction);
    exit(5);
  }
}

/* ====================================================================================== */

int isPot2(int n)
{
  int k;
  return (k = log2(n)) == log2(n) ;
}

/* ====================================================================================== */

void** mallocMatrix(int lin, int col, unsigned int varSize){
  void** mat;
  int i;

  int paddedCol = isPot2(col) ? col + PADDING : col;

  mat = mallocCheck(lin * sizeof(void*), "allocating line pointers for matrix");
  mat[0] = mallocCheck(lin * paddedCol * varSize, "allocating element vector");

  for(i = 1; i < lin; i++)
    mat[i] = mat[0] + i * paddedCol * varSize;

  return mat;
}

/* ====================================================================================== */

void matrixDestructor(void** mat){
  free(mat[0]);
  free(mat);
}

/* ====================================================================================== */

double timestamp(void) {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return((double)(tp.tv_sec*1.0e3 + tp.tv_nsec*1.0e-6));
}

/* ====================================================================================== */

FILE* openFile(char* path, char* mode){
  FILE* file = fopen(path, mode);
    
  if(!file){
    fprintf(stderr, "Error opening %s\n", path);
    exit(OPENING_FILE_ERROR);
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
        exit(USAGE_ERROR);
    }

    option = getopt(argc, argv, args);
  }
}

/* ====================================================================================== */

double norm(double* v, unsigned int n) {
  double max = fabs(v[0]);
  for (int i = 1; i < n; i++) {
    if(fabs(v[i]) > max)
      max = fabs(v[i]);
  }

  return max;
}

/* ====================================================================================== */

int notEndLine(char* buffer){
  return buffer[0] != '\n';
}

/* ====================================================================================== */

void printOutput(FILE* output, sl* linSys) {
  fprintf(output, "%d\n", linSys->d);
  fprintf(output, "%s\n", linSys->f->strFunc);
  fprintf(output, "#\n");
  fprintf(output, "Iteração \t| Newton Padrão \t| Newton Inexato\n");

  for(int i = 0; i < linSys->maxIter + 1; i++){
    if(
      linSys->out->newtonInexact <= i 
      && linSys->out->newtonLU <= i 
      && linSys->out->newtonExact <= i
    )
      break;
    fprintf(output,"%d \t\t| ", i);
    double** mat = linSys->out->output;

    if(linSys->out->newtonExact > i){
      double value = mat[NEWTON_EXACT][i];
      if(isnan(value) || isinf(value))
        fprintf(output, "%1.14e\t\t\t| ", value);
      else 
        fprintf(output, "%1.14e\t| ", value);
    }
    else
      fprintf(output, "\t\t\t| ");

    if(linSys->out->newtonInexact > i){
      double value = mat[NEWTON_INEXACT][i];
      if(isnan(value) || isinf(value))
        fprintf(output, "%1.14e\t\t\t ", value);
      else 
        fprintf(output, "%1.14e\t ", value);
    }
    else
      fprintf(output, "\t\t\t ");

    fprintf(output, "\n");
  }
  fprintf(output, "Tempo total \t| %1.14e \t| %1.14e\n", linSys->out->total[NEWTON_EXACT], linSys->out->total[NEWTON_INEXACT]);
  fprintf(output, "Tempo derivadas | %1.14e \t| %1.14e\n", linSys->f->derivativeTime, linSys->f->derivativeTime);
  fprintf(output, "Tempo SL \t| %1.14e \t| %1.14e\n", linSys->out->system[NEWTON_EXACT], linSys->out->system[NEWTON_INEXACT]);
  fprintf(output, "#\n");
  fprintf(output, "\n");
}

/* ====================================================================================== */

void showMatrix(double** A, double *b, int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      printf("%f ", A[i][j]);
    }
    printf("| %f\n", b[i]);
  }
  printf("\n");
}

/* ====================================================================================== */

void showMatrixInt(double** A, int *b, int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      printf("%f ", A[i][j]);
    }
    printf("| %d\n", b[i]);
  }
  printf("\n");
}

/* ====================================================================================== */

char *  markerName(char *  baseName, int n)
{
  char *  mark = (char * ) malloc( (strlen(baseName)+1) + (log10(n)+1) + 1 );

  sprintf(mark, "%s_%u", baseName,n);

  // printf("*** %s\n", mark);

  return mark;

}

/* ====================================================================================== */

