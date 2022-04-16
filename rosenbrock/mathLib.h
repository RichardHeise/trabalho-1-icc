/**
 *  This file contains the headers for the functions in mathLib.c
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#ifndef MATH_SNL_H
#define MATH_SNL_H

#define ASSERTING_ERROR 1

// Struct to store a function 
typedef struct S_Function{
  double derivativeTime; // Time to mathEval to calculate a derivative
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

#endif