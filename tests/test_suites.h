#ifndef TEST_SUITES_H
#define TEST_SUITES_H

#include "../include/arguments.h"
#include "../include/file_list.h"
#include "../include/thread_queue.h"
#include "../include/threading.h"

void setup_global_test_env();
void run_test_case(const char* label, int argc, char** argv, int expected_count, const char** expected_names);
void validateResult(const char* label, FileList* result, int expected_count, const char** expected_names);

void run_basic_tests();
void run_combination_tests();

#endif
