#include "../include/arguments.h"
#include "../include/file_list.h"
#include "../include/directory_traversal.h"
#include "../include/thread_queue.h"
#include "../include/threading.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv)
{


  Argument arg;
  parseArguments(&arg, argc, argv);

  FilterFunc activeFilters[5];
  int filterCount = initFilter(activeFilters, &arg);
  
  FileList result; initList(&result);
  
  TaskQueue queue; initQueue(&queue);

  //check if from pipeline
  if (!isatty(STDIN_FILENO)) {
    char startPath[PATH_MAX];
    while (fgets(startPath, sizeof(startPath), stdin)) {
      int index=strcspn(startPath, "\n");
      startPath[index] = '\0';

      if (strlen(startPath) > 0) {
        pushTask(&queue, startPath, &result);
      }
    }
  }
  else{
    pushTask(&queue, arg.startPath, &result);
  }
  
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

  if(arg.humanReadable){
    printHumanReadableList(&result);
  }
  else{
    printList(&result);
  }
  
  freeList(&result);
  freeQueue(&queue);


  return 0;
}

