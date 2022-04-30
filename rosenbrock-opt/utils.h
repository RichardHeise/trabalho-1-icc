/**
 *  This file contains the headers for the functions in utils.c
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdio.h>
#include "newton.h"
#include <likwid.h>

#define OPENING_FILE_ERROR 2
#define MEM_ALLOC_ERROR 3
#define USAGE_ERROR 4
#define PADDING 1
/**
 * Receives int size
 * Receives char* error 
 * Function to check and malloc an array
 * Returns a pointer to a now allocated region
 */
void* mallocCheck(int size, char* error);

/**
 * Receives int lin
 * Receives int col
 * Function to malloc a matrix in memory
 * Returns a dynamically allocated matrix
 */
void** mallocMatrix(int lin, int col, unsigned int varSize);

/**
 * Receives double** mat
 * Function to destroy a matrix
 */
void matrixDestructor(void** mat);

/**
 * Returns current time
 */
double timestamp(void);

/**
 * Receives int arc
 * Receives char** argv
 * Receives const char *args
 * Receives FILE** valueO
 * Parse possible arguments for the program 
 */
void parseArgs(int argc, char** argv, const char *args, FILE** valueO);

/**
 * Receives double* vector
 * Receives unsigned int n
 * Function to get a norm of an array
 * Returns a double value
 */ 
double norm(double* vector, unsigned int n);

/**
 * Receives char* buffer
 * Returns true if buffer is not a '\n'
 */ 
int notEndLine(char* buffer);

/**
 * Receives FILE* output
 * Receives sl* linSys
 * Function to print the output
 */
void printOutput(FILE* output, sl* linSys);

/**
 * Receives double** A
 * Receives int* b
 * Receives int n 
 * Prints a matrix with a int b array
 */
void showMatrixInt(double** A, int *b, int n);

/**
 * Receives double** A
 * Receives double* b
 * Receives int n 
 * Prints a matrix with a double b array
 */
void showMatrix(double** A, double *b, int n);


/**
 * Receives int denominator
 * Receives char* function name 
 * checks if denominator is 0
 */
void checkZeroDivision(double denominator, char* funcName, char* cFunction);

char *  markerName(char *  baseName, int n);

#endif