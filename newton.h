#ifndef NEWTON_H
#define NEWTON_H

#include "mathLib.h"

typedef struct S_SL {
    function* f;
    double** Hi;
    double* Gi;
    double* nGi;
    double* Xi;
    double* deltai;
    unsigned int d;
    double eps;
    unsigned int maxIter;
} sl;

sl* slConstructor(char* func);

void slDestructor(sl* sisLin);

void newtonDefault(sl* sisLin);

#endif 