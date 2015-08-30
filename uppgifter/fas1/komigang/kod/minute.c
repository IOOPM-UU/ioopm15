#include "minute.h"
#include<stdio.h>

unsigned int	tests_failed	= 0;
unsigned int	tests_succeeded = 0;

void __minute__assert(char* name, int success_p) {
  printf("Testing %s ... ", name);
  if (success_p) {
    ++tests_succeeded;
    puts("PASSED");
  } else {
    ++tests_failed;
    puts("FAILED");
  }
}

void report() {
  if (tests_failed) {
    printf("Passed: %d\n", tests_succeeded);
    printf("Failed: %d\n", tests_failed);
    printf("Total number of tests: %d\n", tests_succeeded + tests_failed);
  } else {
    printf("All %d test passed!\n", tests_succeeded + tests_failed);
  }
}
