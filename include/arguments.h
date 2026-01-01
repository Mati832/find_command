
#ifndef arguments
#define arguments



typedef struct{
  char *startPath;
  char *namePattern;
  char type;
  char *filterCondition;
  int recursive;
}Argument;

void parseArguments(Argument *argument, int argc, char **argv);

#endif
