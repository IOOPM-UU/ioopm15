#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef void *T;

struct dyn_array
{
  uint16_t capacity; // 64K element max
  T *elements;
};

typedef struct dyn_array dyn_array_t;

dyn_array_t darray_make(uint16_t capacity)
{
  // OBS! Borde göra felkontroll!
  return (dyn_array_t) {
    .capacity = capacity,
      .elements = calloc(capacity, sizeof(T)) };
}

void darray_free(dyn_array_t &arr)
{
  // TODO!!
}

T darray_get(dyn_array_t arr, uint16_t idx)
{
  return (idx < arr.capacity) ? arr.elements[idx] : NULL;
}

bool darray_set(dyn_array_t arr, uint16_t idx, T elem)
{
  if (idx < arr.capacity)
    {
      arr.elements[idx] = elem;
      return true;
    }

  return false;
}

void darray_append(dyn_array_t *arr, T elem)
{
  int max = arr->capacity;
  
  arr->capacity *= 2;
  arr->elements = realloc(arr->elements, arr->capacity * sizeof(T));

  arr->elements[max] = elem;
}

void darray_prepend(dyn_array_t *arr, T elem)
{
  arr->capacity *= 2;
  arr->elements = realloc(arr->elements, arr->capacity * sizeof(T));

  for (int i = arr->capacity; i > 0; --i)
    {
      arr->elements[i] = arr->elements[i-1];
    }

  arr->elements[0] = elem;
}

uint16_t darray_size(dyn_array_t arr)
{
  return arr.capacity;
}
