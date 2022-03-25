#ifndef UTILS_H
#define UTILS_H

void* mallocCheck(int size, char* error);

double** mallocMatrix(int lin, int col);

void matrixDestructor(double** mat);

#endif