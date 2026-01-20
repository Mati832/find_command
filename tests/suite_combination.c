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


    // TEST 6: Name + Size Filter
    // We search for files containing "Byte" in name AND are larger than 50 bytes.
    // 10Byte.txt  -> Matches Name, Fails Size (>50)
    // 200Byte.txt -> Matches Name, Matches Size (>50) -> TARGET
    
    char* t6[] = {"findClone", "test_root", "-name", "*Byte*", "-size", "+50"};
    const char* exp6[] = {"test_root/200Byte.txt"};
    run_test_case("Combo: Name + Size (>50)", 6, t6, 1, exp6);

    // TEST 7: Name + Mtime Filter
    // We search for files with "daysago" in name AND are older than 3 days.
    // 5daysago.txt  (5 days old)  -> Matches Name, Matches Time (>3) -> TARGET
    // 10daysago.txt (10 days old) -> Matches Name, Matches Time (>3) -> TARGET
    // today.txt                   -> Fails Name, Fails Time
    
    char* t7[] = {"findClone", "test_root", "-name", "*daysago*", "-mtime", "+3"};
    const char* exp7[] = {
        "test_root/5daysago.txt",
        "test_root/10daysago.txt"
    };
    run_test_case("Combo: Name + Time (>3 days)", 6, t7, 2, exp7);



    // TEST 8: Size + Recursion
    // Find all files larger than 5 bytes in the whole tree.
    // Only 10Byte.txt and 200Byte.txt have content. Others are 0 bytes.
    
    char* t8[] = {"findClone", "test_root", "-size", "+5", "-r"};
    const char* exp8[] = {
        "test_root/10Byte.txt",
        "test_root/200Byte.txt"
    };
    run_test_case("Combo: Size + Rec (>5 bytes)", 5, t8, 2, exp8);

    
    // TEST 9: Name + Mtime Filter (Impossible Case)
    // Find a file that is "today.txt" BUT is older than 2 days.
    // Should return NOTHING.
    
    char* t9[] = {"findClone", "test_root", "-name", "today.txt", "-mtime", "+2"};
    run_test_case("Combo: Impossible Time", 6, t9, 0, NULL);

}

