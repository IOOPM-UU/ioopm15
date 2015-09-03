#include <stdio.h>
#include <stdlib.h>

long fib(const int n)
{
  switch (n)
    {
    case 0:  return 0;
    case 1:  return 1;
    default: return fib(n - 1) + fib(n - 2);
    }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      printf("Usage: %s <n>\n", argv[0]);
    }
  else
    {
      const int n = atoi(argv[1]);
      printf("fib(%d) = %zd\n", n, fib(n));
    }

  return 0; 
}
