#ifndef MATH_SNL_H
#define MATH_SNL_H

typedef struct SVariables{
  char** variables;
  double* values;
}variables;

typedef struct SFunction{
  void* f;
  variables* vars;
}function;

void* getFunction(char* func);


#endif