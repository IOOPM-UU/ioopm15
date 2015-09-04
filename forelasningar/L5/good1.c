#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
  size_t bufsiz = 2048;
  char buffer[bufsiz];

  puts("Skriv en rad:");

  fgets(buffer, bufsiz, stdin);

  printf("Du skrev: %s", buffer);
  
  return 0;
}
