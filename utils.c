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

double** mallocMatrix(int lin, int col){
  double** mat;
  int i;

  mat = mallocCheck(lin * sizeof(double*), "allocating line pointers for matrix");
  mat[0] = mallocCheck(lin * col * sizeof(double), "allocating element vector");

  for(i = 1; i < lin; i++)
    mat[i] = mat[0] + i * col;

  return mat;
}

void matrixDestructor(double** mat){
  free(mat[0]);
  free(mat);
}
