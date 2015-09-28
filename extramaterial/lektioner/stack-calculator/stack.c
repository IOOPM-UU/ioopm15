#include "stack.h"
#include <stdlib.h>

struct node {
  void *elem;
  struct node *next;
};

struct node *node_new(void *elem, struct node *next) {
  struct node *n = malloc(sizeof(struct node));
  n->elem = elem;
  n->next = next;
  return n;
}

struct stack {
  int size;
  struct node *top;
};

// Make a new stack
stack *stack_new() {
  struct stack *s = malloc(sizeof(struct stack));
  if(s != NULL) {
    s->size = 0;
    s->top = NULL;
  }
  return s;
}

// Remove a stack from memory
void stack_free(stack *s) {
  free(s);
}

// Push elem to s
void stack_push(stack *s, void *elem) {
  s->top = node_new(elem, s->top);
  s->size++;
}

bool stack_empty(stack *s) {
  if(s->top == NULL) {
    return true;
  } else {
    return false;
  }
}

// Pop an element from s. Returns NULL if s is empty
void *stack_pop(stack *s) {
  if(stack_empty(s)) {
    return NULL;
  }
  struct node *old_top = s->top;
  struct node *new_top = old_top->next;
  s->top = new_top;
  void *elem = old_top->elem;
  free(old_top);
  s->size--;
  return elem;
}

// Return the top element of s. Returns NULL if s is empty
void *stack_top(stack *s) {
  if(stack_empty(s)) {
    return NULL;
  }
  return s->top->elem;
}

// Return the number of elements in the stack
int stack_size(stack *s) {
  return s->size;
}

// An iterator for the stack
typedef struct iterator iter_t;

// Initialize an iterator
iter_t *iterator_new(stack *s);

// Return current element and move i forward
void *iterator_next(iter_t *i);

// true if i has more elements, false otherwise
bool iterator_more(iter_t *i);

// Remove an iterator from memory
void iterator_free(iter_t *i);
