/**
 *  Arquivo com os cabeçalhos das funções de utils.c
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#ifndef UTILS_H
#define UTILS_H

/**
 * Recebe int size
 * Recebe char* error 
 * Função para conferir se uma matriz foi alocada
 * Retorna um ponteiro para uma região alocada
 */
void* mallocCheck(int size, char* error);

/**
 * Recebe int lin
 * Recebe int col
 * Função para alocar uma matriz na memória
 * Retorna uma matriz alocada dinamicamente
 */
double** mallocMatrix(int lin, int col);

/**
 * Recebe double** mat
 * Função para destruir uma matriz
 */
void matrixDestructor(double** mat);

#endif