#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

#include "arguments.h"
#include "filter.h"

void test(const char *filename, char op, long days)
{
    struct stat st;
    Argument arg;

    memset(&arg, 0, sizeof(Argument));
    arg.useMtime = 1;
    arg.mtimeOp = op;
    arg.mtimeValue = days;

    if (stat(filename, &st) != 0) {
        perror("stat failed");
        return;
    }

    int result = mtimeFilter(filename, &st, &arg);

    printf("Test: %s  -mtime %c%ld  -> %s\n",
           filename,
           op,
           days,
           result ? "MATCH" : "NO MATCH");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *file = argv[1];

    printf("Testing mtime filter for file: %s\n\n", file);

    test(file, ‘+’, 1);  // Is it older than 1 day?
    test(file, ‘-’, 1);  // Is it within the last 1 day?
    test(file, ‘=’, 0);  // Has it changed today?
    test(file, ‘=’, 1);  // Was it exactly 1 day ago?

    return 0;
}
