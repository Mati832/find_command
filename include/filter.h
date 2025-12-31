#ifndef filter
#define filter


typedef int (*FilterFunc)(const struct dirent *entry, const Argument *argument);

#endif
