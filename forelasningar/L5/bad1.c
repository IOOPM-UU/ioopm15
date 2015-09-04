#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *input = NULL;
  size_t input_len = 0;

  puts("Skriv en rad:");
  getline(&input, &input_len, stdin);

  printf("Du skrev: %s", input);

  return 0;
}
