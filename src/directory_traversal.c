#include <dirent.h>
#include "../include/file_list.h"
#include "../include/arguments.h"
#include "../include/filter.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1


void traverseDirectory(FileList *result
                       ,const char *startPath
                       ,FilterFunc filters[]
                       , int filterCount
                       ,const Argument *argument){
  struct dirent *entry;
  DIR *dir = opendir(startPath);

  if(!dir) return;

  while ( (entry=readdir(dir)) != NULL){

    int matches=TRUE;

    for (int i=0; i<filterCount && matches; i++) {
      matches=filters[i](entry, argument);
    }

    if(matches){
      char fullPath[PATH_MAX];
      snprintf(fullPath, sizeof(fullPath), "%s/%s",startPath,entry->d_name);
      addFile(result, fullPath);
    }
  }
  closedir(dir);
}
