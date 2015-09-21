#include <stdio.h>
#include <stdlib.h>

// ================================================================
// Välj ett av nedanstående bibliotek
// ================================================================
// #include "stack.h"
#include "stack2_0.h"


int main(int argc, char *argv[])
{
  int_stack_t *s = stack_new();
  
  bool error;
  
  for (int i = 1; i < argc; ++i)
    {
      int v = atoi(argv[i]);

      if (v >= 0)
	{
	  stack_push(s, v, &error);
	}
      else
	{
	  stack_pop(s, &error);
	}
    }

  while (stack_height(s))
    {
      printf("%d\n", stack_pop(s, &error));
    }

  stack_free(s);
  
  return 0;
}
