/**
 *  Arquivo com os cabeçalhos das funções de mathLib.c
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#ifndef MATH_SNL_H
#define MATH_SNL_H

// Struct para guardar as variáveis da equação
typedef struct SVariables{
  char** variables;
  int varAmount;
}variables;

// Struct para guardar o valor da função, da derivada e as variáveis da função
typedef struct SFunction{
  void* f;
  void** dfs;
  variables* vars;
}function;

/**
 * Recebe char* func
 * Função para construir uma function no formato de mathEval
 * Retorna um ponteiro para function
 */
function* functionConstructor(char* func);

/**
 * Recebe char* func
 * Função para destruir a function do formato de mathEval
 */
void functionDestructor(function *func);

/**
 * Recebe function* f
 * Função para resgatar as variáveis de uma function
 */
void showVariables(function* f);

/**
 * Recebe function* f
 * Função para resgatar as derivadas de uma function
 */
void showDerivatives(function* f);

/**
 * Recebe function* f
 * Função para resgatar uma function
 */
void showFunction(function* f);

#endif