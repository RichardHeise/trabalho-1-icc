/**
 *  This file contains the implementations of newton related methods
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#include <matheval.h>
#include <stdlib.h>
#include <string.h>
#include "rosenbrock.h"
#include <likwid.h>
#include "newton.h"
#include "methods.h"
#include "utils.h"

output* outputConstructor(int maxIter){
    output* out = mallocCheck(sizeof(output), "allocating output structure");
    out->output = (double**) mallocMatrix(NUM_METHODS, maxIter + 1, sizeof(double));
    out->newtonExact = 0;
    out->newtonInexact = 0;
    out->total = mallocCheck(sizeof(double) * NUM_METHODS, "allocating double total time array");
    out->system = mallocCheck(sizeof(double) * NUM_METHODS, "allocating double linear system time array");

    return out;
}

/* ====================================================================================== */

void outputDestructor(output* out){
    matrixDestructor((void**) out->output);
    free(out->total);
    free(out->system);
    free(out);
}

/* ====================================================================================== */

sl* slConstructor(char* func, int numVars) {
    sl* linSys = mallocCheck(sizeof(sl), "allocating memory for linear system."); 
    linSys->f = functionConstructor(func);
    int n = numVars;
    
    linSys->eps = 0.000001;
    linSys->maxIter = 0;
    linSys->d = n;
    linSys->Hi = (double**) mallocMatrix(n, n, sizeof(double));
    linSys->Gi = mallocCheck(sizeof(double) * n, "allocating memory for gradient array of linear system.");
    linSys->nGi = mallocCheck(sizeof(double) * n, "allocating memory for negated gradient array of linear system.");
    linSys->deltai = mallocCheck(sizeof(double) * n, "allocating memory for delta array.");
    linSys->Xi = mallocCheck(sizeof(double) * n, "allocating memory for variables array of linear system.");
    linSys->Xinit = mallocCheck(sizeof(double) * n, "allocating memory for variables array of linear system.");

    return linSys;
}

/* ====================================================================================== */

void slDestructor(sl* linSys) {
    functionDestructor(linSys->f);
    matrixDestructor((void**) linSys->Hi);
    outputDestructor(linSys->out);
    free(linSys->Gi);
    free(linSys->nGi);
    free(linSys->Xi);
    free(linSys->Xinit);
    free(linSys->deltai);
    free(linSys);
}

/* ====================================================================================== */

void handleSlInit(sl** linSys, int i, char* buffer, int* numVars){
  double num;
  int pos;
  char* p;
  int k = 0;
  
  // For each block line we do something different
  switch (i){
        case 0:
            *numVars = atoi(buffer);
            break;
        case 1: // Reads function
          (*linSys) = slConstructor(buffer, *numVars);
          break;
        case 2: // Reads initial X values
          p = buffer; 
          while(k < (*linSys)->d && (sscanf(p, "%lf %n", &num, &pos) > 0 && p[0])) {
            (*linSys)->Xi[k] = num;
            (*linSys)->Xinit[k] = num;
            p += pos;
            k++;
          }
          break;
        case 3: // Reads error
          (*linSys)->eps = strtod(buffer, NULL);
          break;
        case 4: // Reads max iterations
          (*linSys)->maxIter = atoi(buffer);
          (*linSys)->out = outputConstructor((*linSys)->maxIter);
          break;
        default:
          break;
      }
}

/* ====================================================================================== */

void registerValue(sl* linSys, int i, int j){
    linSys->out->output[i][j] = rosenbrock_f(linSys->Xi, linSys->d);
}

/* ====================================================================================== */

void newtonDefault(sl* linSys) {
    int i, j;

    // Register output
    registerValue(linSys, NEWTON_EXACT, 0);
    linSys->out->newtonExact = 1;

    for (i = 0; i < linSys->maxIter; i++) {
        char* name = markerName("n_newtonDefault_gradient", linSys->d);
        LIKWID_MARKER_START(name);

        calcGradient(linSys);

        LIKWID_MARKER_STOP(name);
        free(name);

        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            return;

        name = markerName("n_newtonDefault_hessian", linSys->d);
        LIKWID_MARKER_START(name);

        calcHessian(linSys);

        LIKWID_MARKER_STOP(name);
        free(name);

        name = markerName("n_newtonDefault_solver", linSys->d);
        LIKWID_MARKER_START(name);

        solveSL(linSys);

        LIKWID_MARKER_STOP(name);
        free(name);
        
        // unroll and jam on J
        for (j = 0; j < linSys->d - (linSys->d % 4); j += 4){
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];
            linSys->Xi[j + 1] = linSys->Xi[j + 1] + linSys->deltai[j + 1];
            linSys->Xi[j + 2] = linSys->Xi[j + 2] + linSys->deltai[j + 2];
            linSys->Xi[j + 3] = linSys->Xi[j + 3] + linSys->deltai[j + 3];
        }
        
        // calculating residue
        for(; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];

        
        registerValue(linSys, NEWTON_EXACT, linSys->out->newtonExact++);

        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            return;
    }
}

/* ====================================================================================== */

void newtonGS(sl* linSys) {
    int i, j;

    registerValue(linSys, NEWTON_INEXACT, 0);
    linSys->out->newtonInexact = 1;

    for (i = 0; i < linSys->maxIter; i++) {
        char* name = markerName("n_newtonGS_gradient", linSys->d);
        LIKWID_MARKER_START(name);
        
        calcGradient(linSys);

        LIKWID_MARKER_STOP(name);
        free(name);

        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            return;

        name = markerName("n_newtonGS_hessian", linSys->d);
        LIKWID_MARKER_START(name);

        calcHessian(linSys);   

        LIKWID_MARKER_STOP(name);
        free(name);

        name = markerName("n_newtonGS_solver", linSys->d);
        LIKWID_MARKER_START(name);

        gaussSeidel(linSys); 

        LIKWID_MARKER_STOP(name);
        free(name);

        // unroll and jam on J
        for (j = 0; j < linSys->d - (linSys->d % 4); j += 4){
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];
            linSys->Xi[j + 1] = linSys->Xi[j + 1] + linSys->deltai[j + 1];
            linSys->Xi[j + 2] = linSys->Xi[j + 2] + linSys->deltai[j + 2];
            linSys->Xi[j + 3] = linSys->Xi[j + 3] + linSys->deltai[j + 3];
        }
        
        // calculating residue
        for(; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];


        registerValue(linSys, NEWTON_INEXACT, linSys->out->newtonInexact++);
        
        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            return;
    }


}

/* ====================================================================================== */

void newtonMod(sl* linSys) {
    int i;
    
    registerValue(linSys, NEWTON_LU, 0);
    linSys->out->newtonLU = 1;

    LU* sysLU;
    sysLU = luConstructor(linSys);
    for (i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        if ( norm(linSys->Gi, linSys->d) < linSys->eps )
            break;
        
        // We calculate the Hessian each degree number times
        if ( !(i % linSys->d) ) {
            calcHessian(linSys);  
            decompLU(sysLU, linSys->f->strFunc); 
        }
        solveLU(linSys, sysLU);

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];

        registerValue(linSys, NEWTON_LU, linSys->out->newtonLU++);
        
        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            break;
    }

    luDestructor(sysLU);
}

/* ====================================================================================== */

sl* copySl(sl* linSys){
    sl* new = slConstructor(linSys->f->strFunc, linSys->d);
    new->d = linSys->d;
    new->eps = linSys->eps;
    new->maxIter = linSys->maxIter;
    memcpy(new->deltai, linSys->deltai, sizeof(double) * linSys->d);
    memcpy(new->Gi, linSys->Gi, sizeof(double) * linSys->d);
    memcpy(new->Hi[0], linSys->Hi[0], sizeof(double) * linSys->d * linSys->d);
    memcpy(new->nGi, linSys->nGi, sizeof(double) * linSys->d);
    memcpy(new->Xi, linSys->Xi, sizeof(double) * linSys->d);

    return new;
}

/* ====================================================================================== */

void resetSl(sl* linSys){
    memcpy(linSys->Xi, linSys->Xinit, sizeof(double) * linSys->d);
}
