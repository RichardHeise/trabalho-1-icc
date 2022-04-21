/**
 *  This file contains the implementations of the functions related to the mathEval lib
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#include <matheval.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mathLib.h"
#include "utils.h"

void* getFunction(char* func){
  void* f = evaluator_create(func);
  if(!f) {
    fprintf(stderr, "Error asserting %s\n", func);
    exit(ASSERTING_ERROR);
  }

  return f;
}

/* ====================================================================================== */

function* functionConstructor(char* func){
  function* f = mallocCheck(sizeof(function), "function pointer");
  f->vars = mallocCheck(sizeof(variables), "function variables");

  f->strFunc = mallocCheck(sizeof(char) * (strlen(func) + 1), "allocating strFunc name");
  strcpy(f->strFunc, func);

  f->f = getFunction(func);
  evaluator_get_variables(f->f, &f->vars->variables, &f->vars->varAmount); 

  f->dfs = mallocCheck(sizeof(void*) * f->vars->varAmount, "function derivatives");
  f->hessian = (void***) mallocMatrix(f->vars->varAmount, f->vars->varAmount, sizeof(void*));
  f->derivativeTime = 0;;


  // Calculate Hessian and second derivatives
  for(int i = 0; i < f->vars->varAmount; i++){
    f->dfs[i] = evaluator_derivative(f->f, f->vars->variables[i]);
  }

  f->derivativeTime = timestamp();
  for(int i = 0; i < f->vars->varAmount; i++){
    for (int j = 0; j < f->vars->varAmount; j++) {
      f->hessian[i][j] = evaluator_derivative(f->dfs[i], f->vars->variables[j]);
    }
  }
  f->derivativeTime = timestamp() - f->derivativeTime;

  return f;
}

/* ====================================================================================== */

void functionDestructor(function *func){
  for (int i = 0; i < func->vars->varAmount; i++) {
    for (int j = 0; j < func->vars->varAmount; j++)
        evaluator_destroy(func->hessian[i][j]);
  }
  for(int i = 0; i < func->vars->varAmount; i++)
    evaluator_destroy(func->dfs[i]);
  evaluator_destroy(func->f);
  free(func->dfs);
  free(func->vars);
  free(func->strFunc);
  matrixDestructor((void**)func->hessian);
  free(func);
}

/* ====================================================================================== */

void showFunction(function* f){
  printf("f(x) = %s\n", evaluator_get_string(f->f));
}

/* ====================================================================================== */

void showVariables(function* f){
  variables* vars = f->vars;
  for(int i = 0; i < vars->varAmount; i++)
    printf("%s ", vars->variables[i]);
  printf("\n");
}

/* ====================================================================================== */

void showDerivatives(function* f){
  void** dfs = f->dfs;
  variables* vars = f->vars;
  for(int i = 0; i < vars->varAmount; i++)
    printf("f'(%s) = %s\n", vars->variables[i], evaluator_get_string(dfs[i]));
}

/* ====================================================================================== */

void showhessian(function* f) {
  void*** hes = f->hessian;
  variables* vars = f->vars;
  for (int i = 0; i < f->vars->varAmount; i++) {
    for (int j = 0; j < f->vars->varAmount; j++) {
      printf("f''(%s, %s) = %s | ", vars->variables[i], vars->variables[j], evaluator_get_string(hes[i][j]));
    }
    printf("\n");
  }
}

