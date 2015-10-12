#ifndef _tree_h_
#define _tree_h_

#include <stdbool.h>
#include <stdlib.h>

typedef struct node node_t;
typedef void(*action_f)(int, void *, void *);

node_t *node_new(int value);
void node_add(node_t **n, int value);
bool node_contains(node_t **n, int value);
node_t **node_find(node_t **n, int value);
void node_forall(node_t *n, action_f f, void *arg1, void *arg2);
int node_size(node_t *);
int node_depth(node_t *);

#endif
