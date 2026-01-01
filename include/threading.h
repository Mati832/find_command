#ifndef threading
#define threading

#include "thread_queue.h"
#include "filter.h"
#include "arguments.h"

void worker(TaskQueue *queue, 
          FilterFunc filters[], 
          int filterCount, 
          Argument *argument);

#endif 

