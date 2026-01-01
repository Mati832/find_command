
#include "../include/thread_queue.h"
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE 0

void initQueue(TaskQueue *queue){
  queue->start=NULL;
  queue->end=NULL;
  sem_init( &queue->mutex, 0, 1 );
  sem_init( &queue->taskCount, 0, 0);
  queue->activeThreads=0;
}

void pushTask(TaskQueue *queue, char *directory, FileList *target){
  
  Task *newTask=malloc(sizeof(Task));

  newTask->next=NULL;
  newTask->directory = (directory != NULL) ? strdup(directory) : NULL;
  newTask->targetList = target;

  sem_wait(&queue->mutex);
  if(queue->start == NULL){
    queue->start=newTask;
    queue->end=newTask;
    
  }
  else{
    queue->end->next=newTask;
    queue->end=newTask;
  }

  sem_post(&queue->mutex);

  sem_post(&queue->taskCount);
}

Task popTask(TaskQueue *queue){
  sem_wait(&queue->taskCount);

  sem_wait(&queue->mutex);

  Task *temp=queue->start;
  Task res;
  
  res.directory=temp->directory;
  res.targetList=temp->targetList;

  queue->start=queue->start->next;

  if(queue->start ==NULL){
    queue->end = NULL;
  }
  
  sem_post(&queue->mutex);
  free(temp);
  
  return res;
}
int isQueueFinished(TaskQueue *queue) {
    int finished = FALSE;
    sem_wait(&queue->mutex); 
    if (queue->start == NULL && queue->activeThreads == 0) {
        finished = TRUE;
    }
    
    sem_post(&queue->mutex);
    return finished;
}

void threadStartedWorking(TaskQueue *queue){
  sem_wait(&queue->mutex);
  queue->activeThreads++;
  sem_post(&queue->mutex);
}

void threadStoppedWorking(TaskQueue *queue){
  sem_wait(&queue->mutex);
  queue->activeThreads--;
  sem_post(&queue->mutex);
}
