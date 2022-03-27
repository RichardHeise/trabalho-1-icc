#include <stdlib.h>
#include "newton.h"
#include "methods.h"
#include "utils.h"

sl* slConstructor(char* func) {
    sl* sisLin = mallocCheck(sizeof(sl), "allocating memory for linear system."); 
    sisLin->f = functionConstructor(func);
    int n = sisLin->f->vars->varAmount;
    
    sisLin->eps = 0.000001;
    sisLin->maxIter = 0;
    sisLin->d = n;
    sisLin->Hi = (double**) mallocMatrix(n, n, sizeof(double));
    sisLin->Gi = mallocCheck(sizeof(double) * n, "allocating memory for gradient array of linear system.");
    sisLin->nGi = mallocCheck(sizeof(double) * n, "allocating memory for negated gradient array of linear system.");
    sisLin->deltai = mallocCheck(sizeof(double) * n, "allocating memory for delta array.");
    sisLin->Xi = mallocCheck(sizeof(double) * n, "allocating memory for variables array of linear system.");


    return sisLin;
}

void slDestructor(sl* sisLin) {
    functionDestructor(sisLin->f);
    matrixDestructor((void**) sisLin->Hi);
    free(sisLin->Gi);
    free(sisLin->nGi);
    free(sisLin->Xi);
    free(sisLin->deltai);
    free(sisLin);
}

void newtonDefault(sl* sisLin) {
    for (int i = 0; i < sisLin->maxIter-1; i++) {
        calcGradient(sisLin);

        if ( norm(sisLin->Gi, sisLin->d) < sisLin->eps ) 
            return;

        calcHessiana(sisLin);   
        solveSL(sisLin);

        for (int j = 0; j < sisLin->d; j++)
            sisLin->Xi[j] = sisLin->Xi[j] + sisLin->deltai[j];
        
        if ( norm(sisLin->deltai, sisLin->d) < sisLin->eps ) 
            return;
        
    }
}

