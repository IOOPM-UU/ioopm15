#include <stdio.h>

int main()
{
  int a[5];

  a[0] = 42;
  a[1] = 10;
  a[2] = 10 - (5 + 6);
  a[3] = a[0] + a[1];
  a[4] = 999;

  for (int i = 0; i < 5; ++i){
    printf("a[%d] = %d\n", i, a[i]);
  }

  return 0;
}