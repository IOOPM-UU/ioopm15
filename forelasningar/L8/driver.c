#include <stdio.h>
#include <stdlib.h>

// ================================================================
// Välj ett av nedanstående bibliotek
// ================================================================
#include "stack.h"
// #include "stack2_0.c"


int main(int argc, char *argv[])
{
  int_stack_t *s = stack_new();

  for (int i = 1; i < argc; ++i)
    {
      int v = atoi(argv[i]);
      if (v >= 0)
	{
	  stack_push(s, v);
	}
      else
	{
	  stack_pop(s);
	}
    }

  while (stack_height(s))
    {
      printf("%d\n", stack_pop(s));
    }

  stack_free(s);
  
  return 0;
}
