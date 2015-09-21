#include <stdio.h>
#include <stdlib.h>
#include "stack2_0.h"

#define Stack_max_size 1024

struct stack
{
  int values[Stack_max_size];
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

/// TODO: underful check
int stack_top(int_stack_t *s, bool *underflow)
{
  if (s->height == 0)
    {
      *underflow = true;
      return 0;
    }
  else
    {
      *underflow = false;
      return s->values[0];
    }
}

/// TODO: overful check
void stack_push(int_stack_t *s, int v, bool *overflow)
{
  if (s->height == Stack_max_size)
    {
      *overflow = true;
      return;
    }
  else
    {
      *overflow = false;
    }
  
  for (int i = s->height; i > 0; --i)
    {
      s->values[i] = s->values[i - 1];
    }

  ++s->height;

  s->values[0] = v;
}

/// TODO: underful check
int stack_pop(int_stack_t *s, bool *underflow)
{
  int result = stack_top(s, underflow); 

  if (*underflow)
    {
      return 0;
    }

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

