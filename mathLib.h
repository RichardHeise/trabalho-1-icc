#ifndef MATH_SNL_H
#define MATH_SNL_H

typedef struct SVariables{
  char** variables;
  int varAmount;
}variables;

typedef struct SFunction{
  void* f;
  void** dfs;
  variables* vars;
}function;

function* functionConstructor(char* func);

void functionDestructor(function *func);

void showVariables(function* f);

void showDerivatives(function* f);

void showFunction(function* f);

#endif