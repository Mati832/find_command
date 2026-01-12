
#define TRUE 1
#define FALSE 0

#include "../include/arguments.h"

#include <stdlib.h> 
#include <string.h>
#include <stdio.h>

void usage(const char *progName) {
    fprintf(stderr, "Usage: %s [path] [-name pattern] [-type f|d] [-size [+|-|=]value] [-mtime [+|-|=]value] [-r]\n", progName);
    exit(EXIT_FAILURE);
}

void parseArguments(Argument *argument, int argc, char **argv){
  argument->startPath = ".";
  argument->namePattern = NULL;
  argument->type = '\0';
  argument->recursive = FALSE;

  /*-size default*/
  argument->sizeOp = 0;
  argument->sizeValue = 0;
  //-mtime
  argument->useMtime=FALSE;
  
  for (int i=1;i<argc;i++) {


    if (strcmp(argv[i], "-name") == 0 || strcmp(argv[i], "-type") == 0 || 
        strcmp(argv[i], "-size") == 0 || strcmp(argv[i], "-mtime") == 0) {
        if (i + 1 >= argc) {
            fprintf(stderr, "Error: Flag '%s' requires an argument.\n", argv[i]);
            usage(argv[0]);
            }
        }

    

    if( (i+1)<argc && strcmp(argv[i], "-name") == 0 ){
      i++;
      argument->namePattern=argv[i];
    }
    else if( (i+1)<argc && strcmp(argv[i], "-type") == 0 ){
      i++;
      char t = *argv[i];
      if(t != 'd' && t != 'f'){
          fprintf(stderr, "Error: Invalid type '%c'. Use 'd' for directory or 'f' for file.\n", t);
          usage(argv[0]);
      }
      argument->type=t;
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
    else if (strcmp(argv[i], "-mtime") == 0 && i + 1 < argc) {
        argument->useMtime = 1;
        i++;
        char *val = argv[i];

        if (val[0] == '+' || val[0] == '-' || val[0] == '=') {
            argument->mtimeOp = val[0];
            argument->mtimeValue = atol(val + 1);
        } 
        else {
            argument->mtimeOp = '=';
            argument->mtimeValue = atol(val);
        }
    }
    else if(i==1){
      argument->startPath=argv[i];
    }
    else{
        fprintf(stderr, "Error: Unknown argument '%s'.\n", argv[i]);
        usage(argv[0]);
    }
  }
}
