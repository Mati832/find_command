#include "../include/arguments.h"
#include "../include/file_list.h"
#include "../include/traverse_directory.h"
#include <stdio.h>

void printArguments(int argc, char **argv);
void printTraverseDirectory(int argc, char **argv);
void printList(FileList *list);

int main(int argc, char **argv)
{
  FileList result;
  initList(&result);
  
  Argument arg;
  parseArguments(&arg, argc, argv);

  FilterFunc activeFilters[5];
  int filterCount = 0;

  if (arg.namePattern != NULL) {
    activeFilters[filterCount] = nameFilter;
    filterCount++;
  }
  if (arg.type != '\0') {
    activeFilters[filterCount] = typeFilter;
    filterCount++;
  }
  
  traverseDirectory(&result, arg.startPath, activeFilters, filterCount, &arg);
  printList(&result); 
  return 0;
}

void printArguments(int argc,char **argv){
  Argument argument;
  parseArguments(&argument, argc, argv);
  printf("startPath: %s\n",argument.startPath);
  printf("namePattern: %s\n",argument.namePattern);
  printf("type: %c\n",argument.type);
  printf("filterCondition: %s\n",argument.filterCondition);
  printf("recursive: %d\n", argument.recursive);
}
void printList(FileList *list){

  FileNode *current=list->start;
  while (current!=NULL) {
    printf("%s\n",current->absolutePath);
    current=current->next;
  }
  freeList(list);
}
