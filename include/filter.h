#ifndef filter
#define filter

#include "arguments.h"


typedef int (*FilterFunc)(const struct dirent *entry, const Argument *argument);

int typeFilter(const struct dirent *entry, const Argument *argument);

int nameFilter(const struct dirent *entry, const Argument *argument);

#endif
