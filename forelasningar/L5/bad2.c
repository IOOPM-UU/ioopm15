#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *whisper(char *s)
{
  char *c = s;
  do
    {
      if (isalpha(*c)) { *c = tolower(*c); }
    }
  while (*c++);
  return s;
}

char *shout(char *s)
{
  char *c = s;
  do
    {
      if (isalpha(*c)) { *c = toupper(*c); }
    }
  while (*c++);
  return s;
}

int main(int argc, char *argv[])
{
  size_t bufsiz = 2048;
  char buffer[bufsiz];

  puts("Skriv en rad:");
  scanf("%s", buffer);

  char *w = whisper(strdup(buffer));
  
  printf("Viska: '%s'\n", w);

  printf("Skrika: '%s'\n", shout(buffer));
  
  return 0;
}
