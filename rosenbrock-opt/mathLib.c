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

function* functionConstructor(char* func){
  function* f = mallocCheck(sizeof(function), "function pointer");

  f->strFunc = mallocCheck(sizeof(char) * (strlen(func) + 1), "allocating strFunc name");
  strcpy(f->strFunc, func);

  f->derivativeTime = 0;

  return f;
}

/* ====================================================================================== */

void functionDestructor(function *func){
  free(func->strFunc);
  free(func);
}

/* ====================================================================================== */