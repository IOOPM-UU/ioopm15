#include <assert.h>
#include "tree.h"

struct node
{
  int value;
  node_t *left;
  node_t *right;
};

node_t *node_new(int value)
{
  node_t *result = calloc(1, sizeof(node_t));
  result->value = value;
  return result;
}

#define Left(n) (&((*n)->left))
#define Right(n) (&((*n)->right))
#define Value(n) ((*n)->value)

void node_add(node_t **n, int value)
{
  node_t **found = node_find(n, value);

  if (*found == NULL)
    {
      *found = node_new(value);
    }
}

bool node_contains(node_t **n, int value)
{
  return *node_find(n, value) != NULL; 
}

node_t **node_find(node_t **n, int value)
{
  if (*n == NULL || Value(n) == value) return n;
  if (Value(n) > value) return node_find(Left(n), value);
  if (Value(n) < value) return node_find(Right(n), value);

  assert(false);
  return NULL; 
}

void node_forall(node_t *n, action_f f, void *arg1, void *arg2)
{
  if (n->left) node_forall(n->left, f, arg1, arg2);
  f(n->value, arg1, arg2);
  if (n->right) node_forall(n->right, f, arg1, arg2);
}
