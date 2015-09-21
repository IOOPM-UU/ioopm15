/** \file util.h

  \brief Utility functions.

*/

#ifndef UTIL_H
#define UTIL_H
#include <string.h>
#include <stdbool.h>

/**
  A function with one pointer arg and no return value.
*/
typedef void (*void_fun_t)(void *);

/**
  A function with two pointer args and no return value.
*/
typedef void (*void_fun2_t)(void *, void *);

/**
  A function with three pointer args and no return value.
*/
typedef void (*void_fun3_t)(void *, void *, void *);

/**
  A comparator is a function that needs to be sideeffect-free and
  symmetric (`fun(x,y)` == `fun(y,x)` for all `x` and `y`).
*/
typedef bool (*comparator_t)(const void *, const void *);

/**
  Test whether two strings are equal.

  \returns `true` iff `strcmp(a, b) == 0`.
*/
bool streq(const void *a, const void *b);

/**
  Print a string.

  Like `puts` but ignores the return value. Can be cast to a \ref
  void_fun_t.
*/
void printstr(void *);

#endif // UTIL_H
