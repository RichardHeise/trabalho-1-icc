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
void elGauss(double** A, double *b, int n);

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
void retroSub(double** A, double* b, double* x, int n);

void calcHessiana(sl* sisLin);

void calcGradient(sl* sisLin);

#endif