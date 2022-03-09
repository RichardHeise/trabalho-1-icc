#include <matheval.h>
#include <stdio.h>
#include <stdlib.h>
#include "mathSNL.h"

void* getFunction(char* func){
  void* f = evaluator_create(func);
  if(!f) {
    fprintf(stderr, "Error asserting %s\n", func);
    exit(1);
  }

  return f;
}