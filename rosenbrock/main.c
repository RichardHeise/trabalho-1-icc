/**
 *  This file contains the main function
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

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
  // Pointer to output file
  FILE* output = NULL;

  parseArgs(argc, argv, "o:h", &output);

  // Declaring variables
  sl* linSys;
  int validBuffer;
  int processSl;
  char* buffer;

  // While we still reading
  for(; !feof(stdin); ){
    
    int numVars = 0;
    validBuffer = fscanf(stdin, "%ms", &buffer) > 0;
    processSl = validBuffer;

    for(int i = 0; i < BLOCK_SIZE && validBuffer; i++){
      // Filters the \n after fscanf
      fgetc(stdin);

      // Handle possible lines in the block
      handleSlInit(&linSys, i, buffer, &numVars);
      
      free(buffer);
      validBuffer = fscanf(stdin, "%m[^\n]", &buffer) > 0;
    }
    
    free(buffer);
    if(processSl){
      // After a method is done, the linear system is reset
      // and the next one is processed
      linSys->out->total[NEWTON_EXACT] = timestamp();
      newtonDefault(linSys);
      linSys->out->total[NEWTON_EXACT] = timestamp() - linSys->out->total[NEWTON_EXACT];
      resetSl(linSys);

      linSys->out->total[NEWTON_INEXACT] = timestamp();
      newtonGS(linSys);
      linSys->out->total[NEWTON_INEXACT] = timestamp() - linSys->out->total[NEWTON_INEXACT];

      printOutput(output, linSys);
      slDestructor(linSys);
    }
    
  }

  return 0;
}

