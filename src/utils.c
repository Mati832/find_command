#include <string.h>
#include <stdio.h>

void format_size_dynamic(long bytes, char *output) {
    const char *units[] = {"B", "K", "M", "G", "T"};
    int i = 0;
    double size = (double)bytes;

    while (size >= 1024 && i < 4) {
        size /= 1024;
        i++;
    }

    // Falls Bytes (B), dann ohne Nachkommastelle
    if (i == 0) {
        sprintf(output, "%4ld%s", bytes, units[i]);
    } else {
        sprintf(output, "%4.1f%s", size, units[i]);
    }
}
