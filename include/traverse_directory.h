#ifndef traverse_directory
#define traverse_directory

#include "arguments.h"
#include "file_list.h"
#include "filter.h"
#include "thread_queue.h"

void traverseDirectory(FileList *result
                        ,const char *startPath
                        ,TaskQueue *queue
                        ,FilterFunc filters[]
                        , int filterCount
                        ,const Argument *argument);
#endif
