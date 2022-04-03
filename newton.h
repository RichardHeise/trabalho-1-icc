/**
 *  This file contains the headers for the functions in newton.h
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#ifndef NEWTON_H
#define NEWTON_H

#include "mathLib.h"

#define NUM_METHODS 3
#define NEWTON_EXACT 0
#define NEWTON_INEXACT 1
#define NEWTON_LU 2
#define BLOCK_SIZE 5

// Struct to manage the output format
typedef struct S_OUTPUT{
    double** output;
    int newtonExact;
    int newtonInexact;
    int newtonLU;
} output;

//Struct to manage a linear system
typedef struct S_SL {
    function* f;    // System function
    double** Hi;    // Hessian matrix values
    double* Gi;     // Gradient array values 
    double* nGi;    // Negated gradient array values
    double* Xinit;  // Initial X array, useful in reset
    double* Xi;     // X array 
    double* deltai; // Delta array
    output* out;    // Output of this linear system
    unsigned int d; // Degree of linear system
    double eps;     // Error 
    unsigned int maxIter; 
} sl;

/**
 * Receives char* func
 * Function to build a linear system
 * Returns sl* 
 */ 
sl* slConstructor(char* func);

/**
 * Receives sl* linSys
 * Function to destroy a linear system
 */ 
void slDestructor(sl* linSys);

/**
 * Receives sl* linSys
 * Function to reset a linear system
 */ 
void resetSl(sl* linSys);

/**
 * Receives sl* linSys
 * Function to copy a linear system
 * Returns sl* 
 */ 
sl* copySl(sl* linSys);

/**
 * Receives int maxIter
 * Function to build a output format
 * Returns output*
 */ 
output* outputConstructor(int maxIter);

/**
 * Receives sl* linSys
 * Function to proccess newton default method
 */ 
void newtonDefault(sl* linSys);

/**
 * Receives sl* linSys
 * Function to proccess newton modified method
 */ 
void newtonMod(sl* linSys);

/**
 * Receives sl* linSys
 * Function to proccess newton inexact method
 */ 
void newtonGS(sl* linSys);

/**
 * Receives sl** linSys
 * Receives int i
 * Receives char* buffer
 * Function to proccess the input
 */ 
void handleSlInit(sl** linSys, int i, char* buffer);

#endif 