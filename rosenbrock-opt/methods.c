/**
 *  This file contains the implementations of the numeric methods
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#include <stdlib.h>
#include <stdio.h>
#include <likwid.h>
#include <matheval.h>
#include <string.h>
#include <math.h>
#include "rosenbrock.h"
#include "methods.h"
#include "utils.h"
#include "newton.h"

int findMax(double** A, int i, int n){
  int index = i;
  for(int j = i + 1; j < n; j++){
    if(A[j][i] > A[index][i])
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

void elGauss(sl* linSys){

  double** A = linSys->Hi;
  double*  b = linSys->nGi;
  int      n = linSys->d;
  int i, j;
  
  for(i = 0; i < n; i++){
    // Partial pivoting
    int pivot = findMax(A, i, n);
    if(pivot != i)
      switchLines(A, b, i, pivot, n);

    // Gauss elimination
    for(int k = i + 1; k < n; k++){
      checkZeroDivision(A[i][i], linSys->f->strFunc, __func__);
      double m = A[k][i] / A[i][i];
      A[k][i] = 0;
      for(j = i + 1; j < n; j++){
        A[k][j] -= m * A[i][j];
      }

      b[k] -= b[i] * m;
    }
  }
}

/* ====================================================================================== */

void retroSub(sl* linSys){

  double** A = linSys->Hi;
  double* b = linSys->nGi;
  double* x = linSys->deltai;
  int n = linSys->d;
  int i, j;

  for(i = n -1; i >= 0; i--){
    x[i] = b[i];
    for(j = i + 1; j < n; j++){
      x[i] -= A[i][j] * x[j];
    }

    checkZeroDivision(A[i][i], linSys->f->strFunc, __func__);
    x[i] /= A[i][i];
  }
}

/* ====================================================================================== */

void calcHessian(sl* linSys) {
  int i, j, ii, jj, istart, iend, jstart, jend;

  for(ii = 0; ii < linSys->d / B_SIZE; ii++){
    istart = ii * B_SIZE; iend = istart + B_SIZE;
    for(jj = 0; jj < linSys->d / B_SIZE; jj++){
      jstart = jj * B_SIZE; jend = jstart + B_SIZE;

        for (i = istart; i < iend; i++) {
          for (j = jstart; j < jend; j += 4) {
            linSys->Hi[i][j] = rosenbrock_dxdy(i, j, linSys->Xi, linSys->d); 
            linSys->Hi[i][j + 1] = rosenbrock_dxdy(i, j + 1, linSys->Xi, linSys->d); 
            linSys->Hi[i][j + 2] = rosenbrock_dxdy(i, j + 2, linSys->Xi, linSys->d); 
            linSys->Hi[i][j + 3] = rosenbrock_dxdy(i, j + 3, linSys->Xi, linSys->d); 
          }
        }
    }
    jstart = jj * B_SIZE;
    for (i = istart; i < iend; i++) {
      for (j = jstart; j < linSys->d; j++) {
        linSys->Hi[i][j] = rosenbrock_dxdy(i, j, linSys->Xi, linSys->d); 
      }
    }
  }

  for(i = ii * B_SIZE; i < linSys->d; i++){
    for(j = 0; j < linSys->d; j++){
      linSys->Hi[i][j] = rosenbrock_dxdy(i, j, linSys->Xi, linSys->d); 
    }
  }
  
}

/* ====================================================================================== */

void calcGradient(sl* linSys) {
  int i;

  for(i = 0; i < linSys->d - (linSys->d % 4); i+=4){
    linSys->Gi[i] = rosenbrock_dx(i, linSys->Xi, linSys->d);
    linSys->Gi[i + 1] = rosenbrock_dx(i + 1, linSys->Xi, linSys->d);
    linSys->Gi[i + 2] = rosenbrock_dx(i + 2, linSys->Xi, linSys->d);
    linSys->Gi[i + 3] = rosenbrock_dx(i + 3, linSys->Xi, linSys->d);

    linSys->nGi[i] = (-1*linSys->Gi[i]);
    linSys->nGi[i + 1] = (-1*linSys->Gi[i + 1]);
    linSys->nGi[i + 2] = (-1*linSys->Gi[i + 2]);
    linSys->nGi[i + 3] = (-1*linSys->Gi[i + 3]);
  }


  for(; i < linSys->d; i++){
    linSys->Gi[i] = rosenbrock_dx(i, linSys->Xi, linSys->d);
    linSys->nGi[i] = (-1*linSys->Gi[i]);
  }


}

/* ====================================================================================== */

void solveSL(sl* linSys) {
  elGauss(linSys);
  retroSub(linSys);
}

/* ====================================================================================== */

// void gaussSeidel(sl* linSys) {
//   int n = linSys->d;
  
//   // 0 in deltai array
//   memset(linSys->deltai, 0, sizeof(double)*linSys->d);
//   double **A = linSys->Hi;
//   double *B = linSys->nGi;
//   double *X = linSys->deltai;
//   double error = 10e-6;

//   int k, i, j;
//   double xk, norm, diff = 0;
//   double s[4], soma;
//   norm=1.0+error;

//   for (k=0; norm > error; ++k) {
//     norm = 0.0;

//     for (i=0; i < n; ++i) {
//       memset(s, 0, sizeof(double)*4);
//       soma = 0;
//       for (j=0; j < i - (i % 4); j+=4){
//         s[0] += A[i][j] * X[j];
//         s[1] += A[i][j + 1] * X[j + 1];
//         s[2] += A[i][j + 2] * X[j + 2];
//         s[3] += A[i][j + 3] * X[j + 3];
//       }

//       for(; j < i; j++)
//         s[0] += A[i][j] * X[j];

//       for (j=i+1; j < n - (n % 4); j += 4){
//         s[0] += A[i][j] * X[j];
//         s[1] += A[i][j + 1] * X[j + 1];
//         s[2] += A[i][j + 2] * X[j + 2];
//         s[3] += A[i][j + 3] * X[j + 3];
//       }

//       for(; j < n; j++)
//         s[0] += A[i][j] * X[j];

//       soma += s[0] + s[1] + s[2] + s[3];
//       fprintf(stderr, "sum: %f\n", soma);

//       checkZeroDivision(A[i][i], linSys->f->strFunc, __func__);
//       xk = (B[i] - soma) / A[i][i];
//       diff = fabs(xk - X[i]);

//       if (diff > norm) norm = diff;
//       X[i] = xk;
//     }
//   }
// }

void gaussSeidel(sl* linSys) {
  int n = linSys->d;
  
  // 0 in deltai array
  memset(linSys->deltai, 0, sizeof(double)*linSys->d);
  double **A = linSys->Hi;
  double *B = linSys->nGi;
  double *X = linSys->deltai;
  double error = 10e-6;

  int k, i, j;
  double s, xk, norm, diff = 0;
  norm=1.0+error;

  for (k=0; norm > error; ++k) {
    norm = 0.0;

    for (i=0; i < n; ++i) {
      for (s=0, j=0; j < i; ++j) s += A[i][j] * X[j];

      for (j=i+1; j < n; ++j) s += A[i][j] * X[j];

      fprintf(stderr, "sum: %f\n", s);

      checkZeroDivision(A[i][i], linSys->f->strFunc, __func__);
      xk = (B[i] - s) / A[i][i];
      diff = fabs(xk - X[i]);

      if (diff > norm) norm = diff;
      X[i] = xk;
    }
  }
}

/* ====================================================================================== */

LU* luConstructor(sl* sysLin) {
  LU* sysLU = mallocCheck(sizeof(LU), "allocating memory for the LU system."); 
  
  int n = sysLU->n = sysLin->d;
  sysLU->L = (double**) mallocMatrix(n, n, sizeof(double));
  sysLU->U = sysLin->Hi;
  sysLU->swap = mallocCheck(sizeof(int) * n, "allocating memory for the index array.");
  sysLU->y = mallocCheck(sizeof(double) * n, "allocating memory for the y array.");

  return sysLU;
}

/* ====================================================================================== */

void luDestructor(LU* sysLU) {
  matrixDestructor((void**) sysLU->L);
  free(sysLU->swap);
  free(sysLU->y);
  free(sysLU);
}

/* ====================================================================================== */

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

/* ====================================================================================== */

void resolve_Ly_b(LU *sysLU, sl* linSys) {

  double** A = sysLU->L;
  double*  b = linSys->nGi;
  double*  x = sysLU->y;
  int      n = sysLU->n;

  for(int i = 0; i < n; i++){
    x[i] = b[sysLU->swap[i]];

    for(int j = 0; j < i; j++)
      x[i] -= A[i][j] * x[j];
    checkZeroDivision(A[i][i], linSys->f->strFunc, __func__);
    x[i] /= A[i][i];
  }
} 

/* ====================================================================================== */

void resolve_Ux_y(LU *sysLU, sl* linSys) {
  double** A = sysLU->U;
  double*  b = sysLU->y;
  double*  x = linSys->deltai;
  int      n = sysLU->n;

  for(int i = n -1; i >= 0; i--){
    x[i] = b[sysLU->swap[i]];

    for(int j = i + 1; j < n; j++)
      x[i] -= A[i][j] * x[j];
    checkZeroDivision(A[i][i], linSys->f->strFunc, __func__);
    x[i] /= A[i][i];
  }
}

/* ====================================================================================== */

void decompLU(LU* sysLU, char* funcName) {
  double** A = sysLU->U;
  int*     b = sysLU->swap;
  int      n = sysLU->n;

  // Creates L matrix with 1's in main diagonal
  for (int i = 0; i < n; i++) {
    // Indexes swap array
    sysLU->swap[i] = i;

    for (int j = 0; j < n; j++) {
      sysLU->L[i][j] = 0;
    }

    sysLU->L[i][i] = 1;
  }
  
  // Gauss elimination with partial pivoting
  for(int i = 0; i < n; i++){
    int pivot = findMax(A, i, n);
    if(pivot != i)
      switchLinesInt(A, b, i, pivot, n);

    for(int k = i + 1; k < n; k++){
      checkZeroDivision(A[i][i], funcName, __func__);
      double m = A[k][i] / A[i][i];
      A[k][i] = 0;
      sysLU->L[k][i] = m;

      for(int j = i + 1; j < n; j++)
        A[k][j] -= m * A[i][j];
    }
  }
}

/* ====================================================================================== */

void solveLU(sl* linSys, LU* sysLU) {
  resolve_Ly_b(sysLU, linSys);
  resolve_Ux_y(sysLU, linSys);
}