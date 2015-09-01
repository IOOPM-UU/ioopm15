#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long fib(const int n) 
{
  long acc1, acc2, temp;

  acc1 = 0;
  acc2 = 1;

  for (int i = 0; i < n; ++i)
    {
      temp = acc2; 
      acc2 += acc1;
      acc1 = temp;
    }

  return acc1;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      puts("Usage: ./fib <n>");
    }
  else
    {
      const int n = atol(argv[1]);
      printf("fib(%d) = %zd\n", n, fib(n));
    }

  return 0; 
}
