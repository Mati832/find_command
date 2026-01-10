
#ifndef arguments
#define arguments



typedef struct{
  char *startPath;
  char *namePattern;
  char type;
  char *filterCondition;
  int recursive;
  char mtimeOp;     // for '+', '-', '='
  long mtimeValue;  // in days
  int useMtime;     // Was mtime used by the user?

  char sizeOp;     
  long sizeValue;  
}Argument;

void parseArguments(Argument *argument, int argc, char **argv);

#endif
