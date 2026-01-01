#include "../include/arguments.h"
#include "../include/file_list.h"
#include "../include/traverse_directory.h"
#include "../include/thread_queue.h"
#include "../include/threading.h"
#include <stdio.h>

void printArguments(int argc, char **argv);
void printTraverseDirectory(int argc, char **argv);
void printList(FileList *list);
void printNodes(Node *current);

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
  TaskQueue queue;
  initQueue(&queue);
  pushTask(&queue, arg.startPath, &result);
  worker(&queue, activeFilters, filterCount, &arg);
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

  printNodes(list->start);
  freeList(list);
}
void printNodes(Node *current){

  while (current!=NULL) {
    printf("%s\n",current->absolutePath);
    if(current->type==NODE_DIR){
      printNodes(current->content->start);
    }
    current=current->next;
  }
}
