#ifndef filter
#define filter

#include "arguments.h"
#include <dirent.h>

typedef int (*FilterFunc)(const struct dirent *entry, const Argument *argument);

int applyFilter(const struct dirent *entry, FilterFunc filters[], int filterCount, const Argument *argument);

int typeFilter(const struct dirent *entry, const Argument *argument);

int nameFilter(const struct dirent *entry, const Argument *argument);

int dotFilter(const struct dirent *entry);

#endif
