#ifndef _stack_h_
#define _stack_h_

typedef struct stack int_stack_t;

int_stack_t *stack_new(void);
void stack_free(int_stack_t *s);
int stack_top(int_stack_t *s);
void stack_push(int_stack_t *s, int v);
int stack_pop(int_stack_t *s);
int stack_height(int_stack_t *s);

#endif
