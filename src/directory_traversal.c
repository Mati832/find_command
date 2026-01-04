

#include "../include/directory_traversal.h"
#include "../include/file_list.h"

#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#define TRUE 1


void traverseDirectory(FileList *result
                       ,const char *startPath
                       ,TaskQueue *queue
                       ,FilterFunc filters[]
                       , int filterCount
                       ,const Argument *argument){

  struct dirent *entry;
  DIR *dir = opendir(startPath);
  if(!dir){
    
    fprintf(stderr, "Could not open directory '%s': %s\n", 
            startPath, strerror(errno));
    return;
  }

 while ((entry = readdir(dir)) != NULL) {

    if (dotFilter(entry)) { continue; }

    char fullPath[PATH_MAX];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", startPath, entry->d_name);

    struct dirent fakeEntry = *entry;
    strncpy(fakeEntry.d_name, fullPath, sizeof(fakeEntry.d_name)-1);
    fakeEntry.d_name[sizeof(fakeEntry.d_name)-1] = '\0';

    int entryMatches = applyFilter(&fakeEntry, filters, filterCount, argument);

    if (entry->d_type == DT_DIR) {
        Node *newNode = NULL;

        if (entryMatches) {
            newNode = addFile(result, fullPath, NODE_DIR);
        }

        if (argument->recursive) {
            if (newNode == NULL) {
                pushTask(queue, fullPath, result);
            } else {
                pushTask(queue, fullPath, newNode->content);
            }
        }
    } else {
        if (entryMatches) {
            addFile(result, fullPath, NODE_FILE);
        }
    }
}
  closedir(dir);
  }
