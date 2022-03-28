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
  sl* linSys2;
  int validBuffer;
  int processSl;
  for(; !feof(stdin); ){
    validBuffer = fscanf(stdin, "%ms", &buffer) > 0;
    processSl = validBuffer;
    for(int i = 0; i < 4 && validBuffer; i++){
      double num;
      char* p;
      unsigned int pos;
      int k = 0;
      
      // filters the \n after fscanf
      fgetc(stdin);

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
      validBuffer = fscanf(stdin, "%m[^\n]", &buffer) > 0;
    }
    
    free(buffer);
    if(processSl){
      linSys2 = copySl(linSys);

      newtonDefault(linSys);

      fprintf(output, "%.8s: %1.14e\n", linSys->f->strFunc, evaluator_evaluate(
        linSys->f->f,
        linSys->d,
        linSys->f->vars->variables,
        linSys->Xi
      ));

      newtonGS(linSys2);

      fprintf(output, "%.8s: %1.14e\n", linSys2->f->strFunc, evaluator_evaluate(
        linSys2->f->f,
        linSys2->d,
        linSys2->f->vars->variables,
        linSys2->Xi
      ));

      printf("\n");

      slDestructor(linSys);
      slDestructor(linSys2);
    }
    
  }

  return 0;
}