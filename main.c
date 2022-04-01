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
  char* buffer;
  sl* linSys;
  int validBuffer;
  int processSl;
  for(; !feof(stdin); ){
    validBuffer = fscanf(stdin, "%ms", &buffer) > 0;
    processSl = validBuffer;
    for(int i = 0; i < 5 && validBuffer; i++){
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

      newtonDefault(linSys);

      resetSl(linSys);
      newtonGS(linSys);

      fprintf(output, "%d\n", linSys->d);
      fprintf(output, "%s\n", linSys->f->strFunc);
      fprintf(output, "Iteração \t| Newton Padrão \t| Newton Modificado \t| Newton Inexato\n");
      for(int i = 0; i < linSys->maxIter + 1; i++){
        if(linSys->out->newtonInexact <= i && linSys->out->newtonExact <= i)
          break;
        fprintf(output,"%d \t\t| ", i);
        double** mat = linSys->out->output;

        if(linSys->out->newtonExact > i){
          double value = mat[NEWTON_EXACT][i];
          if(isnan(value) || isinf(value))
            fprintf(output, "%1.14e\t\t\t| ", value);
          else 
            fprintf(output, "%1.14e\t| ", value);
        }
        else
          fprintf(output, "\t\t\t| ");

        fprintf(output, "\t\t\t| ");

        if(linSys->out->newtonInexact > i){
          double value = mat[NEWTON_INEXACT][i];
          if(isnan(value) || isinf(value))
            fprintf(output, "%1.14e\t\t\t ", value);
          else 
            fprintf(output, "%1.14e\t ", value);
        }
        else
          fprintf(output, "\t\t\t ");

        fprintf(output, "\n");
      }

      printf("\n");

      slDestructor(linSys);
    }
    
  }

  return 0;
}