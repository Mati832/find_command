
#define TRUE 1

#include "../include/directory_traversal.h"
#include <stdlib.h>


void worker(TaskQueue *queue, FilterFunc filters[], int filterCount, Argument *argument){
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
                         filters,
                         filterCount,
                         argument);

    free(current.directory);

    threadStoppedWorking(queue);

    if(isQueueFinished(queue)){
      pushTask(queue, NULL, NULL);
    }
  }
}
