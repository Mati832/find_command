#include "test_suites.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    
#include <sys/stat.h>    
#include <pthread.h>


void create_file_with_content(const char *path, int size_in_bytes) {
    FILE *f = fopen(path, "w");
    if (f == NULL) return;
    
    for (int i = 0; i < size_in_bytes; i++) {
        fputc('A', f); // Filling file with 'A's
    }
    fclose(f);
}




void setup_global_test_env() {
    system("rm -rf test_root");
    mkdir("test_root", 0777);
    mkdir("test_root/docs", 0777);
    mkdir("test_root/src", 0777);
    mkdir("test_root/src/backup", 0777);

    system("touch test_root/readme.txt");
    system("touch test_root/image.jpg");
    
    system("touch test_root/docs/plan.txt");
    system("touch test_root/docs/notes.pdf");
    
    system("touch test_root/src/main.c");
    system("touch test_root/src/utils.c");
    system("touch test_root/src/backup/old_main.c");

    create_file_with_content("test_root/10Byte.txt", 10);
    create_file_with_content("test_root/200Byte.txt", 200);
}

void validateResult(const char* label, FileList* result, int expected_count, const char** expected_names) {
    int match_errors = 0;
    
    if (result->count != expected_count) {
        match_errors++;
    }

    // 2. Prüfen: Fehlt eine erwartete Datei?
    for (int i = 0; i < expected_count; i++) {
        int found = 0;
        Node *current = result->start;
        while (current != NULL) {
            if (strcmp(current->absolutePath, expected_names[i]) == 0) {
                found = 1;
                break;
            }
            current = current->next;
        }
        if (!found) {
            if (match_errors == 1 && result->count == expected_count) printf("\n❌ Inhaltsfehler in Test '%s':\n", label);
            printf("   Missing File: %s\n", expected_names[i]);
            match_errors++;
        }
    }

    // 3. Prüfen: Ist eine Datei zu viel drin?
    Node *current = result->start;
    while (current != NULL) {
        int expected = 0;
        for (int i = 0; i < expected_count; i++) {
            if (strcmp(current->absolutePath, expected_names[i]) == 0) {
                expected = 1;
                break;
            }
        }
        if (!expected) {
            printf("   Falsely found: %s\n", current->absolutePath);
            match_errors++;
        }
        current = current->next;
    }

    // Finale Statusmeldung
    printf("%-30s | Expected: %-2d | Is: %-2d | %s\n", 
           label, expected_count, result->count, (match_errors == 0) ? "✅ PASS" : "❌ FAIL");
}

void run_test_case(const char* label, int argc, char** argv, int expected_count, const char** expected_names) {
    Argument arg;
    parseArguments(&arg, argc, argv);

    FilterFunc activeFilters[5];
    int filterCount = initFilter(activeFilters, &arg);
    
    FileList result;
    initList(&result);
    
    TaskQueue queue;
    initQueue(&queue);

    pushTask(&queue, arg.startPath, &result);
    
    WorkerArgument work = {
        .queue = &queue,
        .filters = activeFilters,
        .filterCount = filterCount,
        .argument = &arg
    };

    int numThreads = 2;
    pthread_t threads[numThreads];
    for (int i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, worker, (void*)&work);
    }
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    validateResult(label, &result, expected_count, expected_names);

    freeList(&result);
    freeQueue(&queue);
}
