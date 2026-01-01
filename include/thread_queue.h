#ifndef thread_queue
#define thread_queue


#include <semaphore.h>
#include "file_list.h"

typedef struct Task{
  char *directory;
  FileList *targetList;
  struct Task *next;
}Task;

typedef struct{
  Task *start;
  Task *end;
  sem_t mutex;
  sem_t taskCount;
  int activeThreads;
}TaskQueue;

void initQueue(TaskQueue *queue);

void pushTask(TaskQueue *queue, char *directory, FileList *target);

Task popTask(TaskQueue *queue);

int isQueueFinished(TaskQueue *queue);

void threadStoppedWorking(TaskQueue *queue);

void threadStartedWorking(TaskQueue *queue);

#endif
