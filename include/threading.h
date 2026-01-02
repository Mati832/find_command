#ifndef threading
#define threading

#include "thread_queue.h"
#include "filter.h"
#include "arguments.h"


typedef struct{
  TaskQueue *queue;
  FilterFunc *filters;
  int filterCount;
  Argument *argument;
}WorkerArgument;

void* worker(void *arg);

#endif 

