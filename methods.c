/**
 *  Arquivo com as implementações dos métodos numéricos
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#include <stdlib.h>
#include <stdio.h>
#include <matheval.h>
#include <string.h>
#include <math.h>
#include "methods.h"
#include "utils.h"
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
void elGauss(sl* linSys){

  double** A = linSys->Hi;
  double*  b = linSys->nGi;
  int      n = linSys->d;
  
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

void retroSub(sl* sysLin){

  double** A = sysLin->Hi;
  double* b = sysLin->nGi;
  double* x = sysLin->deltai;
  int n = sysLin->d;

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

void calcHessiana(sl* linSys) {
  for (int i = 0; i < linSys->d; i++) {
    for (int j = 0; j < linSys->d; j++) {
      linSys->Hi[i][j] = evaluator_evaluate(
        linSys->f->hessiana[i][j], 
        linSys->d, 
        linSys->f->vars->variables, 
        linSys->Xi
      );
    }
  }
}

void calcGradient(sl* linSys) {
  for(int i = 0; i < linSys->d; i++){
    linSys->Gi[i] = evaluator_evaluate(
      linSys->f->dfs[i],
      linSys->d,
      linSys->f->vars->variables,
      linSys->Xi
    );

    linSys->nGi[i] = (-1*linSys->Gi[i]);
  }
}

void solveSL(sl* linSys) {
  elGauss(linSys);
  retroSub(linSys);
}

void gaussSeidel(sl* linSys) {
  int n = linSys->d;
  
  memset(linSys->deltai, 0, sizeof(double)*linSys->d);
  double **A = linSys->Hi;
  double *B = linSys->nGi;
  double *X = linSys->deltai;
  double erro = 10e-6;

  int k, i, j;
  double s, xk, norma, diff = 0;
  norma=1.0+erro;

  for (k=0; norma > erro; ++k) {
    norma = 0.0;

    for (i=0; i < n; ++i) {
      for (s=0, j=0; j < i; ++j) s += A[i][j] * X[j];

      for (j=i+1; j < n; ++j) s += A[i][j] * X[j];

      xk = (B[i] - s) / A[i][i];

      diff = fabs(xk - X[i]);

      if (diff > norma) norma = diff;

      X[i] = xk;
    }
  }
}

LU* luConstructor(sl* sysLin) {
  LU* sysLU = mallocCheck(sizeof(LU), "allocating memory for the LU system."); 
  
  int n = sysLU->n = sysLin->d;
  sysLU->L = (double**) mallocMatrix(n, n, sizeof(double));
  sysLU->U = sysLin->Hi;
  sysLU->trocas = mallocCheck(sizeof(int) * n, "allocating memory for the index array.");
  sysLU->y = mallocCheck(sizeof(double) * n, "allocating memory for the y array.");

  decompLU(sysLU);
  return sysLU;
}

void luDestructor(LU* sysLU) {
    matrixDestructor((void**) sysLU->L);
    free(sysLU->trocas);
    free(sysLU->y);
    free(sysLU);
}

void switchLinesInt(double** A, int* b, int i, int pivot, int n){
  double temp = b[i];
  b[i] = b[pivot];
  b[pivot] = temp;

  for(int j = i; j < n; j++){
    temp = A[i][j];
    A[i][j] = A[pivot][j];
    A[pivot][j] = temp; 
  }

}

void elGaussLU(LU* sysLU){

  double** A = sysLU->U;
  int*     b = sysLU->trocas;
  int      n = sysLU->n;

  for (int i = 0; i < n; i++) {
    sysLU->trocas[i] = i;

    for (int j = 0; j < n; j++) {
      sysLU->L[i][j] = 0;
    }

    sysLU->L[i][i] = 1;
  }
  
  for(int i = 0; i < n; i++){
    int pivot = findMax(A, i, n);
    if(pivot != i)
      switchLinesInt(A, b, i, pivot, n);

    for(int k = i + 1; k < n; k++){
      double m = A[k][i] / A[i][i];
      A[k][i] = 0;
      sysLU->L[k][i] = m;
      for(int j = i + 1; j < n; j++)
        A[k][j] -= m * A[i][j];
    }
  }
}

void retroSubInf(LU* sysLU, sl* linSys){

  double** A = sysLU->U;
  double*  b = linSys->nGi;
  double*  x = sysLU->y;
  int      n = sysLU->n;

  for(int i = 0; i < n; i++){
    x[i] = b[sysLU->trocas[i]];
    for(int j = i + 1; j < n; j++)
      x[i] -= A[i][j] * x[j];
    x[i] /= A[i][i];
  }

}

void retroSubSup(LU* sysLU, sl* linSys){

  double** A = sysLU->U;
  double*  b = sysLU->y;
  double*  x = linSys->deltai;
  int      n = sysLU->n;

  for(int i = n -1; i >= 0; i--){
    x[i] = b[i];
    for(int j = i + 1; j < n; j++)
      x[i] -= A[i][j] * x[j];
    x[i] /= A[i][i];
  }

}

void resolve_Ly_b(LU *sysLU, sl* linSys) {
  retroSubInf(sysLU, linSys);
} 

void resolve_Ux_y(LU *sysLU, sl* linSys) {
  retroSubSup(sysLU, linSys);
}

void decompLU(LU* sysLU) {
  elGaussLU(sysLU);
}

void factLU(sl* linSys) {
  LU* sysLU;
  sysLU = luConstructor(linSys);
  resolve_Ly_b(sysLU, linSys);
  resolve_Ux_y(sysLU, linSys);
  luDestructor(sysLU);
}