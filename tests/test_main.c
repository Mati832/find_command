#include "test_suites.h"
#include <stdio.h>


int main() {
    setup_global_test_env(); // Einmaliges Erstellen der Ordnerstruktur

    run_basic_tests();       // Aus suite_basic.c
    run_combination_tests(); // Aus suite_combination.c

    printf("\nTests completed.\n");
    return 0;
}
