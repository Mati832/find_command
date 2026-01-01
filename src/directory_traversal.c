#include <dirent.h>
#include "../include/file_list.h"
#include "../include/arguments.h"
#include "../include/filter.h"
#include "../include/thread_queue.h"
#include <limits.h>
#include <stdio.h>

#define TRUE 1


void traverseDirectory(FileList *result
                       ,const char *startPath
                       ,TaskQueue *queue
                       ,FilterFunc filters[]
                       , int filterCount
                       ,const Argument *argument){

  struct dirent *entry;
  DIR *dir = opendir(startPath);
  if(!dir) return;

  while ( (entry=readdir(dir)) != NULL){

    if(dotFilter(entry)){ continue; }
    int entryMatches=applyFilter(entry, filters, filterCount, argument);

    char fullPath[PATH_MAX];
    snprintf(fullPath, sizeof(fullPath), "%s/%s",startPath,entry->d_name);

    if(entry->d_type == DT_DIR){
      Node *newNode=NULL;
      if(entryMatches) { newNode=addFile(result, fullPath, NODE_DIR); }     

      if(argument->recursive) { 
        if(newNode == NULL){
          pushTask(queue, fullPath, result);
        }
        else{
          pushTask(queue, fullPath, newNode->content);
        }
      }
    }
    else{
      if(entryMatches) {addFile(result, fullPath, NODE_FILE);}
    }
  }
  closedir(dir);
}
