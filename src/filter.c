
#include "../include/filter.h"

#include <fnmatch.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

//only inits lambda-able filter
int initFilter(FilterFunc filters[], Argument *arg){
  int filterCount = 0;

  if (arg->namePattern != NULL) {
    filters[filterCount] = nameFilter;
    filterCount++;
  }
  if (arg->type != '\0') {
    filters[filterCount] = typeFilter;
    filterCount++;
  }
  return filterCount;
}
//only applies lambda-able filter
int applyFilter(const struct dirent *entry, FilterFunc filters[], int filterCount, const Argument *argument){

  int matches=TRUE;
  for (int i=0; i<filterCount; i++) {
    matches=filters[i](entry, argument);
    if(!matches)break;
  }
  return matches;
}

//lambda-able
int typeFilter(const struct dirent *entry, const Argument *argument) {
    if (argument->type == 'd' && entry->d_type == DT_DIR) {
        return TRUE;
    }
    if (argument->type == 'f' && entry->d_type == DT_REG) {
        return TRUE;
    }
    return FALSE;
}
//lambda-able
int nameFilter(const struct dirent *entry, const Argument *argument) {
    if (fnmatch(argument->namePattern, entry->d_name, 0) == 0) {
        return TRUE;
    }

    return FALSE;
}
//not lambda-able
int dotFilter(const struct dirent *entry){
  if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
    return TRUE;
  }
  return FALSE;
}
