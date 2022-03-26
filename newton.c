#include <stdlib.h>
#include "newton.h"
#include "utils.h"

sl* slConstructor(char* func) {
    sl* sisLin = mallocCheck(sizeof(sl), "allocating memory for linear system."); 
    sisLin->f = functionConstructor(func);
    int n = sisLin->f->vars->varAmount;
    
    sisLin->d = n;
    sisLin->Hi = (double**) mallocMatrix(n, n, sizeof(double));
    sisLin->Gi = mallocCheck(n, "allocationg memory for gradient array of linear system.");
    sisLin->Xi = mallocCheck(n, "allocationg memory for variables array of linear system.");

    return sisLin;
}

void slDestructor(sl* sisLin) {
    functionDestructor(sisLin->f);
    matrixDestructor((void**) sisLin->Hi);
    free(sisLin->Gi);
    free(sisLin->Xi);
    free(sisLin);
}
