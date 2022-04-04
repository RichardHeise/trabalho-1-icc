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
  double derivativeTime; // Time to mathEval to calculate a derivative
  void*** hessian; 
  char* strFunc; // String of the function
} function;

/**
 * Receives char* func
 * Function to build a function(type) in mathEval format
 * Returns function*
 */
function* functionConstructor(char* func);

/**
 * Receives char* func
 * Function to destroy a function(type) in mathEval format
 */
void functionDestructor(function *func);

/**
 * Receives function* f
 * Function to print variables of function(type) f
 */
void showVariables(function* f);

/**
 * Receives function* f
 * Function to print derivatives of function(type) f
 */
void showDerivatives(function* f);

/**
 * Receives function* f
 * Function to print a function(type)
 */
void showFunction(function* f);

/**
 * Receives function* f
 * Function to print the Hessian of a function(type)
 */
void showHessiana(function* f);

#endif