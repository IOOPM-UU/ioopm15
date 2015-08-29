#include <stdio.h>

int main(int argc, char *argv[])
{
  int acc1, acc2, temp;

  acc1 = 0;
  acc2 = 1;
 
  const int n = 15; // <---- ÄNDRA DENNA RAD för att ändra vad programmet skall räkna ut

  for (int i = 0; i < n; ++i)
    {
      temp = acc2; 
      acc2 += acc1;
      acc1 = temp;
    }

  printf("fib(%d) = %d\n", n, acc1);

  return 0; 
}
