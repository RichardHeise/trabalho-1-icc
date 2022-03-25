#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include "utils.h"
#include "methods.h"
#include "mathLib.h"

int main(void){
  function* f = functionConstructor("-log(1-x1-x2)-log(x1)-log(x2)");
  double teste[] = {1, 2};
  printf("value: %f\n", evaluator_evaluate(f->dfs[0] , f->vars->varAmount, f->vars->variables, teste));  
  showFunction(f);
  showVariables(f);
  showDerivatives(f);
  functionDestructor(f);
  printf("\n\n");
  
  int n = 3;
  // double A[3][3] = {{2, 3, 4}, {1, 3, 4}, {7, 8, 7}};
  double** A = mallocMatrix(n, n);
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

  printf("\n");
  showMatrix(A, b, n);
  elGauss(A, b, n);
  retroSub(A, b, x, n);
  showMatrix(A, b, n);
  printf("\n");
  for(int i = 0; i < n; i++){
    printf("%f\n", x[i]);
  }

  matrixDestructor(A);

  return 0;
}