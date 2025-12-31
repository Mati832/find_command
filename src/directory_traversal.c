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

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    int matches=TRUE;

    for (int i=0; i<filterCount && matches; i++) {
      matches=filters[i](entry, argument);
    }

    char fullPath[PATH_MAX];
    snprintf(fullPath, sizeof(fullPath), "%s/%s",startPath,entry->d_name);

    if(matches){
      addFile(result, fullPath);
    }
    if(entry->d_type == DT_DIR && argument->recursive){
      traverseDirectory(result, fullPath, filters, filterCount, argument);
    }
  }
  closedir(dir);
}
