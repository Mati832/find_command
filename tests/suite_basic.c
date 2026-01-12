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

void run_basic_tests() {
    // Test 1: Namensfilter
    char* t1[] = {"findClone", "test_root", "-name", "*.jpg"};
    const char* exp1[] = {"test_root/image.jpg"};
    run_test_case("Basic Name (*.jpg)", 4, t1, 1, exp1);

    char* t2[] = {"findClone", "test_root", "-name", "*.c", "-r"};
    const char* exp2[] = {"test_root/src/main.c",
                          "test_root/src/utils.c",
                          "test_root/src/backup/old_main.c"};
    run_test_case("Recursion Name (*.c)", 5, t2, 3, exp2);


    // Test 2: Typfilter (Verzeichnisse)
    char* t3[] = {"findClone", "test_root", "-type", "d"};
    const char* exp3[] = {"test_root/docs", "test_root/src"};
    run_test_case("Basic Type (d)", 4, t3, 2, exp3);
 
    char* t4[] = {"findClone", "test_root/src", "-type", "f", "-r"};
    const char* exp4[] = {"test_root/src/main.c",
                          "test_root/src/utils.c",
                          "test_root/src/backup/old_main.c"};
    run_test_case("Basic Type (f)", 5, t4, 3, exp4);

  //Test 3: StartPath 
      char* t5[] = {"findClone", "test_root/readme.txt"};
      const char* exp5[] = {"test_root/readme.txt"};
      run_test_case("StartPath is File", 2, t5, 0, exp5);

      char* t6[] = {"findClone", "./test_root/docs", "-name", "*.pdf"};
      const char* exp6[] = {"./test_root/docs/notes.pdf"};
      run_test_case("StartPath with ./ prefix", 4, t6, 1, exp6);

      char* t7[] = {"findClone", "falscher/pfad"};
      run_test_case("Invalid StartPath", 2, t7, 0, NULL);

      system("mkdir -p test_root/empty_dir");
      char* t8[] = {"findClone", "test_root/empty_dir", "-r"};
      run_test_case("Empty Directory StartPath", 3, t8, 0, NULL);
}
