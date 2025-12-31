#ifndef traverse_directory
#define traverse_directory

#include <dirent.h>
#include "arguments.h"
#include "file_list.h"
#include "filter.h"

void traverseDirectory(FileList *result
                        ,const char *startPath
                        ,FilterFunc filters[]
                        , int filterCount
                        ,const Argument *argument);
#endif
