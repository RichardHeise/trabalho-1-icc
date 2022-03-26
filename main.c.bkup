#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include "utils.h"
#include "methods.h"
#include "mathLib.h"
#include "newton.h"

int main(void){
  // function* f = functionConstructor("-log(1-x1-x2)-log(x1)-log(x2)");
  sl* sis_lin = slConstructor("-log(1-x1-x2)-log(x1)-log(x2)");
  double teste[] = {0.85, 0.05};
  printf("value: %f\n", evaluator_evaluate(sis_lin->f->dfs[0] , sis_lin->f->vars->varAmount, sis_lin->f->vars->variables, teste));  
  showFunction(sis_lin->f);
  showVariables(sis_lin->f);
  showDerivatives(sis_lin->f);
  sis_lin->Xi[0] = 0.85;
  sis_lin->Xi[1] = 0.05;
  calcGradient(sis_lin);
  for(int i = 0; i < 2; i++){
    printf("%f ", sis_lin->Gi[i]);
  }
  printf("\n\n");
  showHessiana(sis_lin->f);
  calcHessiana(sis_lin);
  showMatrix(sis_lin->Hi, teste, 2);
  
  int n = 3;
  // double A[3][3] = {{2, 3, 4}, {1, 3, 4}, {7, 8, 7}};
  double** A = (double**) mallocMatrix(n, n, sizeof(double));
  A[0][0] = 2;
  A[0][1] = 20;
  A[0][2] = 4;
  A[1][0] = 1;
  A[1][1] = 3;
  A[1][2] = 4;
  A[2][0] = 7;
  A[2][1] = 8;
  A[2][2] = 7;
  double b[] = {5, 5, 6};
  double x[n];

  showMatrix(A, b, n);
  elGauss(A, b, n);
  retroSub(A, b, x, n);
  showMatrix(A, b, n);
  printf("\n");
  for(int i = 0; i < n; i++){
    printf("%f\n", x[i]);
  }

  matrixDestructor((void**)A);
  
  slDestructor(sis_lin);
  
  return 0;
}