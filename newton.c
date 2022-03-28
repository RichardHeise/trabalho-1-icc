#include <stdlib.h>
#include <string.h>
#include "newton.h"
#include "methods.h"
#include "utils.h"

sl* slConstructor(char* func) {
    sl* linSys = mallocCheck(sizeof(sl), "allocating memory for linear system."); 
    linSys->f = functionConstructor(func);
    int n = linSys->f->vars->varAmount;
    
    linSys->eps = 0.000001;
    linSys->maxIter = 0;
    linSys->d = n;
    linSys->Hi = (double**) mallocMatrix(n, n, sizeof(double));
    linSys->Gi = mallocCheck(sizeof(double) * n, "allocating memory for gradient array of linear system.");
    linSys->nGi = mallocCheck(sizeof(double) * n, "allocating memory for negated gradient array of linear system.");
    linSys->deltai = mallocCheck(sizeof(double) * n, "allocating memory for delta array.");
    linSys->Xi = mallocCheck(sizeof(double) * n, "allocating memory for variables array of linear system.");


    return linSys;
}

void slDestructor(sl* linSys) {
    functionDestructor(linSys->f);
    matrixDestructor((void**) linSys->Hi);
    free(linSys->Gi);
    free(linSys->nGi);
    free(linSys->Xi);
    free(linSys->deltai);
    free(linSys);
}

void newtonDefault(sl* linSys) {
    for (int i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            return;

        calcHessiana(linSys);   
        solveSL(linSys);

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];
        
        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            return;
        
    }
}

void newtonGS(sl* linSys) {
    for (int i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        // here we have x
        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            return;

        calcHessiana(linSys);   
        gaussSeidel(linSys); 

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];
        
        // here x+1 has been calculated
        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            return;
    }
}

sl* copySl(sl* linSys){
    sl* new = slConstructor(linSys->f->strFunc);
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
