#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "methods.h"
#include "mathLib.h"
#include "newton.h"


int main(int argc, char** argv){
  FILE* output = NULL;

  parseArgs(argc, argv, "o:h", &output);
  sl* linSys;
  int validBuffer;
  int processSl;
  char* buffer;
  for(; !feof(stdin); ){
    validBuffer = fscanf(stdin, "%ms", &buffer) > 0;
    processSl = validBuffer;
    for(int i = 0; i < BLOCK_SIZE && validBuffer; i++){
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
            linSys->Xinit[k] = num;
            p += pos;
            k++;
          }
          break;
        case 3:
          linSys->eps = strtod(buffer, NULL);
          break;
        case 4:
          linSys->maxIter = atoi(buffer);
          linSys->out = outputConstructor(linSys->maxIter);
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

      //newtonDefault(linSys);
      
      //resetSl(linSys);

      newtonMod(linSys);

      printf("Valor aplicado:%1.14e \n", evaluator_evaluate(
        linSys->f->f, 
        linSys->d, 
        linSys->f->vars->variables, 
        linSys->Xi
      ));


      // resetSl(linSys);
      // newtonGS(linSys);

      // printOutput(output, linSys);

      slDestructor(linSys);
    }
    
  }

  return 0;
}

