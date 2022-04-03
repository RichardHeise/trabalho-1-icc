/**
 *  This file contains the headers for the functions in mathLib.c
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#ifndef MATH_SNL_H
#define MATH_SNL_H

// Struct to store function variables
typedef struct S_Variables{
  char** variables;
  int varAmount;
} variables;

// Struct to store a function 
typedef struct S_Function{
  void* f; // Function 
  void** dfs; // Derivativee of the function
  variables* vars; // Variables
  void*** hessian; 
  char* strFunc; // String of the function
} function;

/**
 * Receives char* func
 * Função para construir uma function no formato de mathEval
 * Retorna um ponteiro para function
 */
function* functionConstructor(char* func);

/**
 * Receives char* func
 * Função para destruir a function do formato de mathEval
 */
void functionDestructor(function *func);

/**
 * Receives function* f
 * Função para resgatar as variáveis de uma function
 */
void showVariables(function* f);

/**
 * Receives function* f
 * Função para resgatar as derivadas de uma function
 */
void showDerivatives(function* f);

/**
 * Receives function* f
 * Função para resgatar uma function
 */
void showFunction(function* f);

/**
 * Receives function* f
 * Função para resgatar uma function
 */
void showHessiana(function* f);

#endif