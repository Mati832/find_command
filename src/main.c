#include "../include/arguments.h"
#include <stdio.h>

void printArguments(int argc, char **argv);


int main(int argc, char **argv)
{
  printArguments(argc, argv);
  return 0;
}

void printArguments(int argc,char **argv){
  Argument argument;
  parseArguments(&argument, argc, argv);
  printf("startPath: %s\n",argument.startPath);
  printf("namePattern: %s\n",argument.namePattern);
  printf("type: %c\n",argument.type);
  printf("filterCondition: %s\n",argument.filterCondition);
}
