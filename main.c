#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include "utils.h"
#include <string.h>
#include "methods.h"
#include "mathLib.h"
#include "newton.h"

int main(int argc, char** argv){
  FILE* output = NULL;

  parseArgs(argc, argv, "o:h", &output);
  char* buffer;
  sl* linSys;

  // double** A = (double**) mallocMatrix(3, 3, sizeof(double));
  // A[0][0] = 20;
  // A[0][1] = 2;
  // A[0][2] = 4;
  // A[1][0] = 1;
  // A[1][1] = 30;
  // A[1][2] = 4;
  // A[2][0] = 7;
  // A[2][1] = 8;
  // A[2][2] = 70;
  // double b[] = {5, 5, 6};
  // double x[3];
  // printf("Antes: \n");
  // showMatrix(A, b, 3);

  // gaussSeidel(A, b, x, 10e-6, 3);

  // printf("Depois: uau\n");
  // showMatrix(A, b, 3);

  // showMatrix(A, x, 3);

  // return 0;

  for(; !feof(stdin); ){
    for(int i = 0; i < 5 && fscanf(stdin, "%m[^\n]", &buffer) > 0; i++){
      // filters the \n at the end of a line after fscanf
      fgetc(stdin);
      
      double num;
      char* p;
      unsigned int pos;
      int k = 0;
      
      switch (i){
        case 1:
          linSys = slConstructor(buffer);
          break;
        case 2:
          p = buffer;
          while(k < linSys->d && (sscanf(p, "%lf %n", &num, &pos) > 0 && p[0])) {
            linSys->Xi[k] = num;
            p += pos;
            k++;
          }
          break;
        case 3:
          linSys->eps = strtod(buffer, NULL);
          break;
        case 4:
          linSys->maxIter = atoi(buffer);
          break;
        case 0:
        default:
          break;
      }
      
      free(buffer);
    }
    
    // memcpy(linSys2, linSys, sizeof(sl));

    // newtonDefault(linSys);

    // fprintf(output, "%.8s: %1.14e\n", linSys->f->strFunc, evaluator_evaluate(
    //   linSys->f->f,
    //   linSys->d,
    //   linSys->f->vars->variables,
    //   linSys->Xi
    // ));

    // printf("\n");

    newtonGS(linSys);

    fprintf(output, "%.8s: %1.14e\n", linSys->f->strFunc, evaluator_evaluate(
      linSys->f->f,
      linSys->d,
      linSys->f->vars->variables,
      linSys->Xi
    ));

    slDestructor(linSys);

    fgetc(stdin);
  }

  return 0;
}