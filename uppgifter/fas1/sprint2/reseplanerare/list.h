/** \file list.h

  \brief A generic linked list implementation.

*/

#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "util.h"

typedef struct _list_t list_t;
typedef struct _iter_t iter_t;

/**
  Create an empty list.
*/
list_t *list_new();

/**
  Add an item to a list (at the end);
*/
void list_add(list_t *, void *);

/**
  Calculate the length of the list.

  \returns The list's length.
*/
int list_len(list_t *);

/**
  Access the nth member of a list. Zero-based.

  `*res` will be assigned to the list element at this location if the
  list is long enough, to `NULL` otherwise.

  \returns `true` if the list is long enough, `false` otherwise.
*/
bool list_nth(list_t *, int n, void **res);

/**
  Test whether a certain element exists.

  \param comp The \ref comparator_t to search with.

  \param elt The element to search for.

  \returns `true` if there is at least one element in the list that,
  compared using the \ref comparator_t, compares equal to `elt`.
*/
bool list_has(list_t *, comparator_t comp, void *elt);

/**
  Iterate over a list.

  Execute the function once for each element in the list and in order.
*/
void list_foreach(list_t *, void_fun_t);

/**
  Create an iterator to a list. Needs to be freed using \ref
  iter_free.

  \sa http://en.wikipedia.org/wiki/Iterator
*/
iter_t *iter(list_t *);

/**
  Advance the iterator by one step.

  \warning Must only be called if \ref iter_done returns `false`.

  \sa iter_done
*/
void iter_next(iter_t *);

/**
  Test whether the iterator has additional elements.

  \returns `true` if the iterator has additional elements, `false`
  otherwise.
*/
bool iter_done(iter_t *);

/**
  Access the current element.

  \returns The current element.
*/
void *iter_get(iter_t *);

/**
  Free the memory allocated by the iterator.
*/
void iter_free(iter_t *);

/**
  Make a shallow clone of a list.

  This operation is *shallow*, it will *not* clone the elements, just
  the list's spine.

  \returns A shallow clone of the list.
*/
list_t *list_clone(list_t *);

/**
  Frees all memory that the list allocated.
*/
void list_free();

#endif // LIST_H
