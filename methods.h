/**
 *  This file contains the headers for the methods.h
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/
 
#ifndef METHODS_H
#define METHODS_H

#include "newton.h"

typedef struct S_LU {
    int n; // Size of matrix
    double **L; // Matrix L from LU
    double **U; // Matrix U from LU
    double *y; // Array y from LU
    int *swap; // Index array for the partial pivoting
} LU;

/**
 * Receives LU* sysLU
 * Function to decompose the linear system in the LU system
 */
void decompLU(LU* sysLU);

/**
 * Receives LU* sysLU
 * Function to build a LU system
 */
LU* luConstructor(sl* sysLin);

/**
 * Receives LU* sysLU
 * Receives sl* linSys
 * Function to solve LY=B
 */
void resolve_Ly_b(LU* sysLU, sl* linSys);

/**
 * Receives LU* sysLU
 * Receives sl* linSys
 * Function to solve UX=Y
 */
void resolve_Ux_y(LU* sysLU, sl* linSys);

/**
 * Receives sl* sysLin
 * Gauss elimination with partial pivoting
 */
void elGauss(sl* sysLin);

/**
 * Receives sl* sysLin
 * Function to apply the retro substitution on the linear system
 */
void retroSub(sl* sysLin);

/**
 * Receives sl* sysLin
 * Function to calculate the Hessian values
 */
void calcHessian(sl* sisLin);

/**
 * Receives sl* sysLin
 * Function to calculate the gradient values
 */
void calcGradient(sl* sisLin);

/**
 * Receives sl* sysLin
 * Function to solve the linear system
 */
void solveSL(sl* linSys);

/**
 * Receives sl* sysLin
 * Function to apply the newton Gauss-Seidel method
 */
void newtonGS(sl* linSys);

/**
 * Receives sl* sysLin
 * Function to solve the linear system using Gauss-Seidel
 */
void gaussSeidel (sl* linSys);

/**
 * Receives sl* sysLin
 * Function to destroy a LU system
 */
void luDestructor(LU* sysLU);

/**
 * Receives double** A
 * Receives int* b
 * Receives int i
 * Receives int pivot
 * Receives int n
 * Function to switch lines using an int array b
 */
void switchLinesInt(double** A, int* b, int i, int pivot, int n);

/**
 * Receives sl* sysLin
 * Receives LU* sysLin
 * Function to solve the LU system
 */
void solveLU(sl* linSys, LU* sysLU);

#endif