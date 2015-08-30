// Föreslagna utökningar:
// 1. Ändra programmet så att det skriver ut i! = ... för varje i i [1..n]
// 2. Lägg till felkontroll: vad händer om man inte ger något argument på kommandoraden?

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int nfak = 1;
  int n = atoi(argv[1]);
  for (int i = 1; i <= n; ++i)
    {
      nfak *= i;
    }
  printf("%d! = %d\n", n, nfak);
  return 0;
}

