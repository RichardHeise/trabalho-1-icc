#include <matheval.h>
#include <stdlib.h>
#include <string.h>
#include "newton.h"
#include "methods.h"
#include "utils.h"

output* outputConstructor(int maxIter){
    output* out = mallocCheck(sizeof(output), "allocating output structure");
    out->output = (double**) mallocMatrix(NUM_METHODS, maxIter + 1, sizeof(double));
    out->newtonExact = 0;
    out->newtonInexact = 0;
    out->newtonLU = 0;

    return out;
}

void outputDestructor(output* out){
    matrixDestructor((void**) out->output);
    free(out);
}

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
    linSys->Xinit = mallocCheck(sizeof(double) * n, "allocating memory for variables array of linear system.");

    return linSys;
}

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

void handleSlInit(sl** linSys, int i, char* buffer){
  double num;
  int pos;
  char* p;
  int k = 0;
  
  switch (i){
        case 1:
          (*linSys) = slConstructor(buffer);
          break;
        case 2:
          p = buffer;
          while(k < (*linSys)->d && (sscanf(p, "%lf %n", &num, &pos) > 0 && p[0])) {
            (*linSys)->Xi[k] = num;
            (*linSys)->Xinit[k] = num;
            p += pos;
            k++;
          }
          break;
        case 3:
          (*linSys)->eps = strtod(buffer, NULL);
          break;
        case 4:
          (*linSys)->maxIter = atoi(buffer);
          (*linSys)->out = outputConstructor((*linSys)->maxIter);
          break;
        case 0:
        default:
          break;
      }
}

void registerValue(sl* linSys, int i, int j){
    linSys->out->output[i][j] = evaluator_evaluate(
        linSys->f->f,
        linSys->d,
        linSys->f->vars->variables,
        linSys->Xi
    );
}

void newtonDefault(sl* linSys) {
    int i;

    registerValue(linSys, NEWTON_EXACT, 0);
    linSys->out->newtonExact = 1;

    for (i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            return;

        calcHessian(linSys);   
        solveSL(linSys);

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];
        
        registerValue(linSys, NEWTON_EXACT, linSys->out->newtonExact++);

        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            return;
    }
}

void newtonGS(sl* linSys) {
    int i;

    registerValue(linSys, NEWTON_INEXACT, 0);
    linSys->out->newtonInexact = 1;

    for (i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        // here we have x
        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            return;

        calcHessian(linSys);   
        gaussSeidel(linSys); 

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];

        registerValue(linSys, NEWTON_INEXACT, linSys->out->newtonInexact++);
        
        // here x+1 has been calculated
        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            return;
    }


}

void newtonMod(sl* linSys) {
    int i;
    
    registerValue(linSys, NEWTON_LU, 0);
    linSys->out->newtonLU = 1;

    LU* sysLU;
    sysLU = luConstructor(linSys);
    for (i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        // here we have x
        if ( norm(linSys->Gi, linSys->d) < linSys->eps )
            return;
        
        if ( !(i % linSys->d) ) {
            calcHessian(linSys);  
            decompLU(sysLU); 
        }
        solveLU(linSys, sysLU);

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];

        registerValue(linSys, NEWTON_LU, linSys->out->newtonLU++);
        
        // here x+1 has been calculated
        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            return;
    }

    luDestructor(sysLU);
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

void resetSl(sl* linSys){
    memcpy(linSys->Xi, linSys->Xinit, sizeof(double) * linSys->d);
}