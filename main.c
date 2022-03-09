#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include "mathSNL.h"

int main(void){
  void* func = getFunction("x^2 + 3*x + 2");
  printf("value: %f\n", evaluator_evaluate_x( func, 2 ));  
  
  return 0;
}