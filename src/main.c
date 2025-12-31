#include "../include/arguments.h"
#include "../include/file_list.h"
#include "../include/traverse_directory.h"
#include <stdio.h>

void printArguments(int argc, char **argv);
void printTraverseDirectory(int argc, char **argv);

int main(int argc, char **argv)
{
  printTraverseDirectory(argc, argv);
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

void printTraverseDirectory(int argc, char **argv){
  Argument argument;
  parseArguments(&argument, argc, argv);
  FileList result;
  initList(&result);
  traverseDirectory(&result
                    , argument.startPath
                    ,NULL
                    ,0
                    ,&argument);

  FileNode *current=result.start;
  while (current!=NULL) {
    printf("%s\n",current->absolutePath);
    current=current->next;
  }
  freeList(&result);
}
