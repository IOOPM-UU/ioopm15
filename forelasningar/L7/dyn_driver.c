#include "dyn_array.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

  dyn_array_t arr = darray_make(4);

  // Store 1,2,3,4 in array
  for (int i = 0; i < darray_size(arr); ++i) darray_set(arr, i, i);

  // Print arr[i] = i for i=[1,4]
  for (int i = 0; i < darray_size(arr); ++i) printf("arr[%d] = %d\n", i, *darray_get(arr, i));

  darray_append(&arr, 5);
  darray_append(&arr, 6);
  darray_prepend(&arr, 7);
  darray_prepend(&arr, 8);

  // Print arr[i] = j for i=[1,8]
  for (int i = 0; i < darray_size(arr); ++i) printf("arr[%d] = %d\n", i, *darray_get(arr, i));

  darray_free(&arr);
  arr = NULL;
  
  return 0;
}
