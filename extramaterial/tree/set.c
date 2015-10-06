#include "tree.h"
#include "set.h"

void add(int value, void *arg1, void *arg2);
void add_if_in_other(int value, void *arg1, void *arg2);
void add_if_not_in_other(int value, void *arg1, void *arg2);
void print(int value, void *arg1, void *arg2);
void count(int element, void *arg1, void *arg2);

struct set
{
  node_t *root; 
};

set_t *set_new()
{
  return calloc(1, sizeof(set_t));
}

void set_free(set_t *s)
{
  // FIXME
}

void set_add(set_t *s, int value)
{
  node_add(&(s->root), value);
}

bool set_contains(set_t *s, int value)
{
  return node_contains(&(s->root), value);
}

void add(int value, void *arg1, void *arg2)
{
  set_add((set_t *)arg1, value);
}

void add_if_in_other(int value, void *arg1, void *arg2)
{
  set_t *other = arg1;
  set_t *result = arg2;

  if (set_contains(other, value))
    {
      set_add(result, value);
    }
}

void add_if_not_in_other(int value, void *arg1, void *arg2)
{
  set_t *other = arg1;
  set_t *result = arg2;

  if (set_contains(other, value) == false)
    {
      set_add(result, value);
    }
}

set_t *set_union(set_t *s1, set_t *s2)
{
  set_t *result = set_new();
  node_forall(s1->root, add, result, NULL);
  node_forall(s2->root, add, result, NULL);
  return result; 
}

set_t *set_intersection(set_t *s1, set_t *s2)
{
  set_t *result = set_new();
  node_forall(s1->root, add_if_in_other, s2, result);
  return result; 
}

set_t *set_subtraction(set_t *s1, set_t *s2)
{
  set_t *result = set_new();
  node_forall(s1->root, add_if_not_in_other, s2, result);
  return result; 
}

void print(int value, void *arg, void *IGNORE2)
{
  int *size = arg;
  if (*size > 0)
    {
      printf("%d, ", value);
    }
  else
    {
      printf("%d", value);
    }
  *size = *size - 1;
}

void set_print(set_t *s)
{
  printf("{");
  int size = set_size(s) - 1;
  node_forall(s->root, print, &size, NULL);
  printf("}");
}

bool set_equal(set_t *s1, set_t *s2)
{
  if (set_size(s1) != set_size(s2)) return false;
      
  set_t *s3 = set_subtraction(s1, s2);
  
  bool result = (set_size(s3) == 0);
  set_free(s3);
  return result;
}

void count(int element, void *arg1, void *arg2)
{
  int *size = arg1; // alt. ++((int *)arg);
  ++*size;
}

int set_size(set_t *s)
{
  if (s->root == NULL) return 0;
  
  int size = 0;
  node_forall(s->root, count, &size, NULL);
  return size;
}
