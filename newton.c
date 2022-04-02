#include <matheval.h>
#include <stdlib.h>
#include <string.h>
#include "newton.h"
#include "methods.h"
#include "utils.h"

output* outputConstructor(int maxIter){
    output* out = mallocCheck(sizeof(output), "allocating output structure");
    out->output = (double**) mallocMatrix(NUM_METHODS, maxIter + 1, sizeof(double));
    out->newtonExact = maxIter + 1;
    out->newtonInexact = maxIter + 1;
    
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

void newtonDefault(sl* linSys) {
    int i;

    linSys->out->output[NEWTON_EXACT][0] = evaluator_evaluate(
        linSys->f->f,
        linSys->d,
        linSys->f->vars->variables,
        linSys->Xi
    );

    for (i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            break;

        calcHessiana(linSys);   
        solveSL(linSys);

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];
        
        linSys->out->output[NEWTON_EXACT][i + 1] = evaluator_evaluate(
            linSys->f->f,
            linSys->d,
            linSys->f->vars->variables,
            linSys->Xi
        );

        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            break;
    }

    linSys->out->newtonExact = i + 1;
}

void newtonGS(sl* linSys) {
    int i;

    linSys->out->output[NEWTON_INEXACT][0] = evaluator_evaluate(
        linSys->f->f,
        linSys->d,
        linSys->f->vars->variables,
        linSys->Xi
    );


    for (i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        // here we have x
        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            break;

        calcHessiana(linSys);   
        gaussSeidel(linSys); 

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];

        linSys->out->output[NEWTON_INEXACT][i + 1] = evaluator_evaluate(
            linSys->f->f,
            linSys->d,
            linSys->f->vars->variables,
            linSys->Xi
        );
        
        // here x+1 has been calculated
        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            break;
    }

    linSys->out->newtonInexact = i + 1;
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

void newtonMod(sl* linSys) {
    int i;

    // linSys->out->output[NEWTON_LU][0] = evaluator_evaluate(
    //     linSys->f->f,
    //     linSys->d,
    //     linSys->f->vars->variables,
    //     linSys->Xi
    // );

    LU* sysLU;
    sysLU = luConstructor(linSys);
    for (i = 0; i < linSys->maxIter; i++) {
        calcGradient(linSys);

        // here we have x
        if ( norm(linSys->Gi, linSys->d) < linSys->eps ) 
            break;
        
        if ( !(i % linSys->d) ) {
            calcHessiana(linSys);  
            decompLU(sysLU); 
        }
        factLU(linSys, sysLU);

        

        for (int j = 0; j < linSys->d; j++)
            linSys->Xi[j] = linSys->Xi[j] + linSys->deltai[j];

        // linSys->out->output[NEWTON_LU][i + 1] = evaluator_evaluate(
        //     linSys->f->f,
        //     linSys->d,
        //     linSys->f->vars->variables,
        //     linSys->Xi
        // );
        
        // here x+1 has been calculated
        if ( norm(linSys->deltai, linSys->d) < linSys->eps ) 
            break;
    }

    luDestructor(sysLU);
    // linSys->out->newtonInexact = i + 1;
}