#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverse_string(char *s) {
  int len = strlen(s);
  char *rev = calloc(len + 1, sizeof(char));
  for (int i = 0; i < len; ++i){
    int j = len - 1 - i;
    rev[j] = s[i];
  }
  rev[len] = '\0';
  return rev;
}

bool strcmp_reverse(char *s1, char *s2) {
  char *rev = reverse_string(s1);
  int result = strcmp(rev, s2);
  free(rev);
  if(result == 0) {
    return true;
  } else {
    return false;
  }
}

int main(int argc, char *argv[]) {
  if(argc < 3) {
    puts("För få argument!");
    return 1;
  }
  char *s1 = argv[1];
  char *s2 = argv[2];
  if(strcmp_reverse(s1, s2)) {
    puts("Samma!");
  } else {
    puts("Inte samma!");
  }
  return 0;
}
