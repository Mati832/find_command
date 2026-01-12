

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

    if (dotFilter(entry)) { continue; }  // Skip "." and ".."

    char fullPath[PATH_MAX];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", startPath, entry->d_name);
    struct stat st;

    if(lstat(fullPath, &st) == -1){
      fprintf(stderr, "Cannot access '%s': %s\n", fullPath, strerror(errno));
      continue;
    }

    int entryMatches = applyFilter(fullPath, &st, filters, filterCount, argument);

    if (S_ISDIR(st.st_mode)) {
        Node *newNode = NULL;

        if (entryMatches) {
            newNode = addFile(result, fullPath, NODE_DIR);
            // Add directory to result list only if it passes filters
        }

        if (argument->recursive) {
            if (newNode == NULL) {
                pushTask(queue, fullPath, result);
                // Save the results flat in the result list
            } else {
                pushTask(queue, fullPath, newNode->content);
                // save the results in the directorys(newNode)list
            }
        }
    }
    else if(entryMatches && S_ISREG(st.st_mode)){
      addFile(result, fullPath, NODE_FILE);
            // Add regular file only if it passes all active filters
    }
}
  closedir(dir);
}
