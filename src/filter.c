
#include "../include/filter.h"
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
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
  if (arg->sizeOp != 0)
    filters[filterCount++] = sizeFilter;

  return filterCount;
}
//only applies lambda-able filter
int applyFilter(const char *fullPath ,const struct stat *st, FilterFunc filters[], int filterCount, const Argument *argument){

  int matches=TRUE;
  for (int i=0; i<filterCount; i++) {
    matches=filters[i](fullPath, st, argument);
    if(!matches)break;
  }
  return matches;
}

//lambda-able
int typeFilter(const char *fullPath, const struct stat *st, const Argument *argument) {
    (void)fullPath;
    if (argument->type == 'd' && S_ISDIR(st->st_mode)) {
        return TRUE;
    }
    if (argument->type == 'f' && S_ISREG(st->st_mode)) {
        return TRUE;
    }
    return FALSE;
}
//lambda-able
int nameFilter(const char *fullPath, const struct stat *st, const Argument *argument) {
  (void)st;

  char *temp = strrchr(fullPath, '/');
    
  const char *fileName = (temp == NULL) ? fullPath : temp + 1;

  if (fnmatch(argument->namePattern, fileName, 0) == 0) {
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

int sizeFilter(const char *fullPath, const struct stat *st, const Argument *arg)
{
    (void)fullPath;
    
    if (!S_ISREG(st->st_mode)) {
        return FALSE;
    }

    if (arg->sizeOp == '+')
        return st->st_size > arg->sizeValue;

    if (arg->sizeOp == '-')
        return st->st_size < arg->sizeValue;

    if (arg->sizeOp == '=')
        return st->st_size == arg->sizeValue;
  
    return FALSE;
}
