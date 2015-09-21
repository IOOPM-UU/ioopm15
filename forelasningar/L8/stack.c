#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack
{
  int values[1024];
  int height;
};

int_stack_t *stack_new(void)
{
  int_stack_t *result = malloc(sizeof(int_stack_t));
  if (result)
    {
      *result = (int_stack_t) { .height = 0 };
    }
  return result;
}

void stack_free(int_stack_t *s)
{
  free(s);
}

int stack_top(int_stack_t *s)
{
  return s->values[0];
}

void stack_push(int_stack_t *s, int v)
{
  for (int i = s->height; i > 0; --i)
    {
      s->values[i] = s->values[i - 1];
    }

  ++s->height;

  s->values[0] = v;
}

int stack_pop(int_stack_t *s)
{
  int result = stack_top(s);

  for (int i = 0; i < s->height; ++i)
    {
      s->values[i] = s->values[i + 1];
    }

  --s->height;

  return result;
}

int stack_height(int_stack_t *s)
{
  return s->height;
}

int domain(int argc, char *argv[])
{
  int_stack_t *s = stack_new();

  for (int i = 1; i < argc; ++i)
    {
      stack_push(s, atoi(argv[i]));
    }

  while (stack_height(s))
    {
      printf("%d\n", stack_pop(s));
    }

  stack_free(s);
  
  return 0;
}
