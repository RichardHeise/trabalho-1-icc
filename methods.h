/**
 *  @file  methods.h
 *  @brief Arquivo com os cabeçalhos 
 *  @date 06/04/2022
 *  @author Gabriel Lüders (GRR20190172)
 *  @author Richard Fernando Heise Ferreira (GRR20191053) 
 **/
 
#ifndef METHODS_H
#define METHODS_H

void elGauss(double** A, double *b, int n);

void showMatrix(double** A, double *b, int n);

void retroSub(double** A, double* b, double* x, int n);

#endif