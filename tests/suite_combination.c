#include "test_suites.h"
#include <stdio.h>

/*
test_root/
├── readme.txt              (Datei)
├── image.jpg               (Datei)
├── docs/                   (Verzeichnis)
│   ├── plan.txt            (Datei)
│   └── notes.pdf           (Datei)
└── src/                    (Verzeichnis)
    ├── main.c              (Datei)
    ├── utils.c             (Datei)
    └── backup/             (Verzeichnis)
        └── old_main.c      (Datei)
*/

void run_combination_tests() {
    printf("\n--- STARTING COMBINATION-TESTS ---\n");
    // Test 1: Name + Typ + Rekursion
    char* t1[] = {"findClone", "test_root", "-name", "*.c", "-type", "f", "-r"};
    const char* exp1[] = {
        "test_root/src/main.c", 
        "test_root/src/utils.c", 
        "test_root/src/backup/old_main.c"
    };
    run_test_case("Combo: Name+Type+Rec", 7, t1, 3, exp1);

    // Test 2: Name + Rekursion (aber nur bestimmte Endung)
    char* t2[] = {"findClone", "test_root", "-name", "plan.txt", "-r"};
    const char* exp2[] = {"test_root/docs/plan.txt"};
    run_test_case("Combo: Deep Name Search", 5, t2, 1, exp2);

    // TEST 3: Alle Dateien in einem spezifischen Unterordner finden
    char* t3[] = {"findClone", "test_root/src", "-type", "f", "-r"};
    const char* exp3[] = {
        "test_root/src/main.c", 
        "test_root/src/utils.c", 
        "test_root/src/backup/old_main.c"
    };
    run_test_case("Deep File Search in /src", 5, t3, 3, exp3);

    // TEST 4: Suche nach Verzeichnissen mit einem bestimmten Namensmuster
    // Prüft, ob der Namensfilter auch auf Ordnernamen greift, wenn -type d aktiv ist.
    char* t4[] = {"findClone", "test_root", "-name", "back*", "-type", "d", "-r"};
    const char* exp4[] = {
        "test_root/src/backup"
    };
    run_test_case("Recursive Directory Name", 7, t4, 1, exp4);


    // TEST 5: Negativ-Test (Keine Treffer trotz Rekursion)
    // Prüft, ob das Programm korrekt "0" zurückgibt, wenn die Kombination unmöglich ist.
    char* t5[] = {"findClone", "test_root", "-name", "*.pdf", "-type", "d", "-r"};
    run_test_case("No Matches (PDF as Dir)", 7, t5, 0, NULL);

}

