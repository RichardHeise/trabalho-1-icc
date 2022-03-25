/**
 *  @file  utils.h
 *  @brief Arquivo com os cabeçalhos das funções de utils.c
 *  @date 06/04/2022
 *  @author Gabriel Lüders (GRR20190172)
 *  @author Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#ifndef UTILS_H
#define UTILS_H

/**
 * @param int size
 * @param char* error 
 * @brief Função para conferir se uma matriz foi alocada
 * @return Retorna um ponteiro para uma região alocada
 */
void* mallocCheck(int size, char* error);

/**
 * @param int lin
 * @param int col
 * @brief Função para alocar uma matriz na memória
 * @return Retorna uma matriz alocada dinamicamente
 */
double** mallocMatrix(int lin, int col);

/**
 * @param double** mat
 * @brief Função para destruir uma matriz
 */
void matrixDestructor(double** mat);

#endif