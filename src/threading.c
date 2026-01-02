
#define TRUE 1

#include "../include/threading.h"
#include "../include/directory_traversal.h"
#include <stdlib.h>
#include <pthread.h>


void* worker(void *input){

  WorkerArgument *arg=(WorkerArgument*) input;
  TaskQueue *queue= arg->queue;

  while (TRUE) {
    Task current=popTask(queue);
    
    if(current.directory==NULL){
      pushTask(queue, NULL, NULL);
      break;
    }
    
    threadStartedWorking(queue);
  
    traverseDirectory(current.targetList,
                         current.directory,
                         queue,
                         arg->filters,
                         arg->filterCount,
                         arg->argument);

    free(current.directory); //da sich in der queue nicht darum gekümmert wird

    threadStoppedWorking(queue);

    if(isQueueFinished(queue)){
      pushTask(queue, NULL, NULL);
    }
  }
  pthread_exit(NULL);
}
