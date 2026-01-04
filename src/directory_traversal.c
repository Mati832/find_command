

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
    // Build full path for the current directory entry

    struct dirent fakeEntry = *entry;
    // Create a local copy of dirent to avoid modifying the original entry

    strncpy(fakeEntry.d_name, fullPath, sizeof(fakeEntry.d_name) - 1);
    fakeEntry.d_name[sizeof(fakeEntry.d_name) - 1] = '\0';
    // Replace d_name with full path so filters can use stat() correctly

    int entryMatches = applyFilter(&fakeEntry, filters, filterCount, argument);
    // Apply filters using the full path (required for -size)

    if (entry->d_type == DT_DIR) {
        Node *newNode = NULL;

        if (entryMatches) {
            newNode = addFile(result, fullPath, NODE_DIR);
            // Add directory to result list only if it passes filters
        }

        if (argument->recursive) {
            if (newNode == NULL) {
                pushTask(queue, fullPath, result);
                // Traverse directory even if it was not added to the result list
            } else {
                pushTask(queue, fullPath, newNode->content);
                // Traverse directory and attach its content to the directory node
            }
        }
    } else {
        if (entryMatches) {
            addFile(result, fullPath, NODE_FILE);
            // Add regular file only if it passes all active filters
        }
    }
}
  closedir(dir);
}
