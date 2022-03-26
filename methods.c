/**
 *  Arquivo com as implementações dos métodos numéricos
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/
 
#include <stdio.h>
#include "methods.h"
#include "newton.h"

int findMax(double** A, int i, int n){
  int index = i;
  for(int j = i + 1; j < n; j++){
    if(A[j][i] > index)
      index = j;
  }
  return index;
}

/* ====================================================================================== */

void switchLines(double** A, double* b, int i, int pivot, int n){
  double temp = b[i];
  b[i] = b[pivot];
  b[pivot] = temp;

  for(int j = i; j < n; j++){
    temp = A[i][j];
    A[i][j] = A[pivot][j];
    A[pivot][j] = temp; 
  }

}

/* ====================================================================================== */
// arriba
void elGauss(double** A, double *b, int n){
  for(int i = 0; i < n; i++){
    int pivot = findMax(A, i, n);
    if(pivot != i)
      switchLines(A, b, i, pivot, n);

    for(int k = i + 1; k < n; k++){
      double m = A[k][i] / A[i][i];
      A[k][i] = 0;
      for(int j = i + 1; j < n; j++)
        A[k][j] -= m * A[i][j];
      b[k] -= b[i] * m;
    }
  }
}

/* ====================================================================================== */

void retroSub(double** A, double* b, double* x, int n){
  for(int i = n -1; i >= 0; i--){
    x[i] = b[i];
    for(int j = i + 1; j < n; j++)
      x[i] -= A[i][j] * x[j];
    x[i] /= A[i][i];
  }
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

void calcHessiana(sl* sisLin) {
  for (int i = 0; i < sisLin->d; i++) {
    for (int j = 0; j < sisLin->d; j++) {
      sisLin->Hi[i][j] = evaluator_evaluate(
        sisLin->f->hessiana[i][j], 
        sis_lin->d, 
        sis_lin->f->vars->variables, sisLin->Xi
      );
    }
  }
}