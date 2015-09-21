#ifndef _stack_h_
#define _stack_h_

#include <stdbool.h>

typedef struct stack int_stack_t;

int_stack_t *stack_new(void);
void stack_free(int_stack_t *s);
int stack_top(int_stack_t *s, bool *underfull);
void stack_push(int_stack_t *s, int v, bool *overfull);
int stack_pop(int_stack_t *s, bool *underfull);
int stack_height(int_stack_t *s);

#endif
