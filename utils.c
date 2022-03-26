/**
 *  Arquivo com as implementações de funções úteis em geral
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/
 
#include <stdlib.h>
#include <stdio.h>
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


double timestamp(void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return((double)(tp.tv_sec*1.0e3 + tp.tv_nsec*1.0e-6));
}
