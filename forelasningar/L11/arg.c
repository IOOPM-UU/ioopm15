#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  char *from = "Ej angivet"; 
  char *to = "Ej angivet"; 
  for (int i = 1; i < argc; ++i)
    {
      if (strcmp(argv[i], "--from") == 0)
        {
          if (i + 1 < argc) from = argv[i+1];
          i = i + 1; 
        }
      if (strcmp(argv[i], "--to") == 0)
        {
          if (i + 1 < argc) to = argv[i+1];
          i = i + 1; 
        }
    }

  printf("Du vill resa från %s till %s\n", from, to);
  return 0;
}

// ./travel --to Centralstationen --from Polackbacken 
// ./travel Centralstationen Polackbacken
