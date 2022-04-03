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

    validBuffer = fscanf(stdin, "%ms", &buffer) > 0;
    processSl = validBuffer;

    for(int i = 0; i < BLOCK_SIZE && validBuffer; i++){
      // Filters the \n after fscanf
      fgetc(stdin);

      // Handle possible lines in the block
      handleSlInit(&linSys, i, buffer);
      
      free(buffer);
      validBuffer = fscanf(stdin, "%m[^\n]", &buffer) > 0;
    }
    
    free(buffer);
    if(processSl){
      // After a method is done, the linear system is reset
      // and the next one is done

      newtonDefault(linSys);
      resetSl(linSys);

      newtonMod(linSys);
      resetSl(linSys);

      newtonGS(linSys);


      printOutput(output, linSys);
      slDestructor(linSys);
    }
    
  }

  return 0;
}

