#include <stdio.h>
int main(int argc, char *argv[]) {
  do {
    puts(*argv);
  } while (*++argv);
  return 0;
}
