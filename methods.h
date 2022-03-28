/**
 *  Arquivo com os cabeçalhos 
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/
 
#ifndef METHODS_H
#define METHODS_H

#include "newton.h"

/**
 * Recebe double** A
 * Recebe double* b
 * Recebe int n 
 * Eliminação de Gauss com pivoteamento
 */
void elGauss(sl* sysLin);

/**
 * Recebe double** A
 * Recebe double* b
 * Recebe int n 
 * Mostra uma matriz na tela
 */
void showMatrix(double** A, double *b, int n);

/**
 * Recebe double** A
 * Recebe double* b
 * Recebe double* x
 * Recebe int n 
 * Realiza a retrosubstituição 
 */
void retroSub(sl* sysLin);

void calcHessiana(sl* sisLin);

void calcGradient(sl* sisLin);

void solveSL(sl* linSys);

void newtonGS(sl* linSys);

void gaussSeidel (sl* linSys);

#endif