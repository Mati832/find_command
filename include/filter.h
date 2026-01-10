#ifndef filter
#define filter

#include "arguments.h"
#include <sys/stat.h>
#include <dirent.h>

typedef int (*FilterFunc)(const char *fullPath, const struct stat *st, const Argument *argument);

int initFilter(FilterFunc filters[], Argument *arg);

  int applyFilter(const char *fullPath, const struct stat *st, FilterFunc filters[], int filterCount, const Argument *argument);

int typeFilter(const char *fullPath, const struct stat *st, const Argument *argument);

int nameFilter(const char *fullPath, const struct stat *st, const Argument *argument);

int dotFilter(const struct dirent *entry);
int sizeFilter(const char *fullPath, const struct stat *st, const Argument *argument);

int mtimeFilter(const char *fullPath, const struct stat *st, const Argument *argument);


#endif
