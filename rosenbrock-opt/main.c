/**
 *  This file contains the main function
 *  Gabriel Lüders (GRR20190172)
 *  Richard Fernando Heise Ferreira (GRR20191053) 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <string.h>
#include <likwid.h>
#include <math.h>
#include "utils.h"
#include "methods.h"
#include "mathLib.h"
#include "newton.h"

int main(int argc, char** argv){
  LIKWID_MARKER_INIT;

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
      char* name = markerName("o_newtonDefault", linSys->d);
      LIKWID_MARKER_START(name);

      newtonDefault(linSys);

      LIKWID_MARKER_STOP(name);
      free(name);
      
      resetSl(linSys);

      name = markerName("o_newtonGS", linSys->d);
      LIKWID_MARKER_START(name);

      newtonGS(linSys);

      LIKWID_MARKER_STOP(name);
      free(name);

      slDestructor(linSys);
    }
    
  }

  LIKWID_MARKER_CLOSE;

  return 0;
}

