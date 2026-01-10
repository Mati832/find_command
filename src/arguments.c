
#define TRUE 1
#define FALSE 0

#include "../include/arguments.h"

#include <stdlib.h> 
#include <string.h>


void parseArguments(Argument *argument, int argc, char **argv){
  argument->startPath = ".";
  argument->namePattern = NULL;
  argument->type = '\0';
  argument->recursive = FALSE;

  /*-size default*/
  argument->sizeOp = 0;
  argument->sizeValue = 0;

  
  for (int i=1;i<argc;i++) {
    
    if (strcmp(argv[i], "-mtime") == 0 && i + 1 < argc) {
    argument->useMtime = 1;

    char *val = argv[i + 1];

    if (val[0] == '+' || val[0] == '-' || val[0] == '=') {
        argument->mtimeOp = val[0];
        argument->mtimeValue = atol(val + 1);
    } else {
        argument->mtimeOp = '=';
        argument->mtimeValue = atol(val);
    }
    i++;
    }    
    if( (i+1)<argc && strcmp(argv[i], "-name") == 0 ){
      i++;
      argument->namePattern=argv[i];
    }
    else if( (i+1)<argc && strcmp(argv[i], "-type") == 0 ){
      i++;
      argument->type=*argv[i];
    }
     else if ((i + 1) < argc && strcmp(argv[i], "-size") == 0) {
            char *value = argv[++i];

            if (value[0] == '+' || value[0] == '-') {
                argument->sizeOp = value[0];
                argument->sizeValue = atol(value + 1);
            } else {
                argument->sizeOp = '=';
                argument->sizeValue = atol(value);
            }
        }
    else if( strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-R") == 0){
      argument->recursive=TRUE;
    }
    else if(i==1){
      argument->startPath=argv[i];
    }
  }
}
