#include <dirent.h>
#include <fnmatch.h>
#include "../include/filter.h"
#define TRUE 1
#define FALSE 0

int typeFilter(const struct dirent *entry, const Argument *argument) {
    if (argument->type == 'd' && entry->d_type == DT_DIR) {
        return TRUE;
    }
    if (argument->type == 'f' && entry->d_type == DT_REG) {
        return TRUE;
    }
    return FALSE;
}

int nameFilter(const struct dirent *entry, const Argument *argument) {
    if (fnmatch(argument->namePattern, entry->d_name, 0) == 0) {
        return TRUE;
    }

    return FALSE;
}
