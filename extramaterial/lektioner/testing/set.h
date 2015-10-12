#ifndef _set_h_
#define _set_h_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "tree.h"

typedef struct set set_t;

set_t *set_new();
void set_free(set_t *s);
void set_add(set_t *s, int value);
bool set_contains(set_t *s, int value);
set_t *set_union(set_t *s1, set_t *s2);
set_t *set_intersection(set_t *s1, set_t *s2);
set_t *set_subtraction(set_t *s1, set_t *s2);
void set_print(set_t *s);
bool set_equal(set_t *s1, set_t *s2);
int set_size(set_t *s);

#endif
