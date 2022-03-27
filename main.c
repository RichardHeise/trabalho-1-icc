#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include "utils.h"
#include "methods.h"
#include "mathLib.h"
#include "newton.h"

int main(int argc, char** argv){
  FILE* output = NULL;

  parseArgs(argc, argv, "o:h", &output);
  char* buffer;
  sl* linSys;
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
    
    newtonDefault(linSys);

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