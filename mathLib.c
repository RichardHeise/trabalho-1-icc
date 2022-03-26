/**
 *  Arquivo com as implementações das funções de gerenciamento da mathEval
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#include <matheval.h>
#include <stdio.h>
#include <stdlib.h>
#include "mathLib.h"
#include "utils.h"

void* getFunction(char* func){
  void* f = evaluator_create(func);
  if(!f) {
    fprintf(stderr, "Error asserting %s\n", func);
    exit(1);
  }

  return f;
}

/* ====================================================================================== */

function* functionConstructor(char* func){
  function* f = mallocCheck(sizeof(function), "function pointer");
  f->vars = mallocCheck(sizeof(variables), "function variables");

  f->f = getFunction(func);
  evaluator_get_variables(f->f, &f->vars->variables, &f->vars->varAmount); 

  f->dfs = mallocCheck(sizeof(void*) * f->vars->varAmount, "function derivatives");
  for(int i = 0; i < f->vars->varAmount; i++){
    f->dfs[i] = evaluator_derivative(f->f, f->vars->variables[i]);
  } 
  return f;
}

/* ====================================================================================== */

void functionDestructor(function *func){
  for(int i = 0; i < func->vars->varAmount; i++)
    evaluator_destroy(func->dfs[i]);
  evaluator_destroy(func->f);
  free(func->dfs);
  free(func->vars);
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
