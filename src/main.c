#include "../include/arguments.h"
#include "../include/file_list.h"
#include "../include/directory_traversal.h"
#include "../include/thread_queue.h"
#include "../include/threading.h"
#include <pthread.h>
#include <stdio.h>

void printArguments(int argc, char **argv);
void printTraverseDirectory(int argc, char **argv);
void printList(FileList *list);
void printNodes(Node *current);

int main(int argc, char **argv)
{


  Argument arg;
  parseArguments(&arg, argc, argv);

  FilterFunc activeFilters[5];
  int filterCount = initFilter(activeFilters, &arg);
  
  FileList result;
  initList(&result);
  
  TaskQueue queue;
  initQueue(&queue);
  pushTask(&queue, arg.startPath, &result);
  
  WorkerArgument work;
  work.queue=&queue;
  work.filters=activeFilters;
  work.filterCount=filterCount;
  work.argument=&arg;

  int numThreads=4;
  pthread_t threads[numThreads];
  for (int i=0; i<numThreads;i++) {
    pthread_create(&threads[i], NULL, worker, (void*)&work);
  }
  for (int i=0; i<numThreads;i++) {
    pthread_join(threads[i],NULL);
  }


  printList(&result);
  
  freeList(&result);
  freeQueue(&queue);


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
