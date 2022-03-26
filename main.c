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
      int k = 0;

      switch (i){
        case 1:
          linSys = slConstructor(buffer);
          break;
        // esse caso 2 tá fazendo com que as coisas deem double free
        case 2:
          while(k < linSys->d && sscanf(buffer, "%lf", &num) > 0){
            linSys->Xi[k] = num;
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
    
    // processar o bloco

    slDestructor(linSys);
    fgetc(stdin);
  }

  return 0;
}