/**
 *  Arquivo com os cabeçalhos 
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/
 
#ifndef METHODS_H
#define METHODS_H

#include "newton.h"

typedef struct S_LU {
    int n; /* dimensão da matriz */
    double **L; /* matriz L da decomposição LU */
    double **U; /* matriz U da decomposição LU */
    double *y; /* vetor de resolucao */
    int *trocas; /* vetor de índices das linhas após trocas efetuadas */
                    /* pelo pivoteamento parcial na decomposição LU */
} LU;

/* Efetua a decomposição LU da matriz M,
 guardando as trocas de linhas no pivoteamento */
void decompLU(LU* sysLU);

LU* luConstructor(sl* sysLin);

/*Resolve o sistema Ly = b aplicando as devidas trocas em b*/
void resolve_Ly_b(LU *sysLU, sl* linSys);

/*Resolve o sistema Ux = y*/
void resolve_Ux_y(LU *sysLU, sl* linSys);

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

void luDestructor(LU* sysLU);

void switchLinesInt(double** A, int* b, int i, int pivot, int n);

void showMatrixInt(double** A, int *b, int n);

void factLU(sl* linSys, LU* sysLU);

#endif