#include "../include/arguments.h"
#include <string.h>
void parseArguments(Argument *argument, int argc, char **argv){
  argument->startPath = ".";
  argument->namePattern = NULL;
  argument->type = ' ';
  argument->filterCondition = NULL;
  

  
  for (int i=1;i<argc;i++) {
    if( (i+1)<argc && strcmp(argv[i], "-name") == 0 ){
      i++;
      argument->namePattern=argv[i];
    }
    else if( (i+1)<argc && strcmp(argv[i], "-type") == 0 ){
      i++;
      argument->type=*argv[i];
    }
    else if( (i+1)<argc && strcmp(argv[i], "-filter") == 0 ){
      i++;
      argument->filterCondition=argv[i];
    }
    else if(i==1){
      argument->startPath=argv[i];
    }
  }
}
