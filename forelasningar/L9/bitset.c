#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct bitset bitset_t;

#define Byte_index(siz,idx) (siz / idx)
#define Bit_index(siz,idx)  (siz % idx)
#define On(a)    1UL << (a)
#define Off(a) ~(1UL << (a))
#define Index_check(a, b) assert(0 <= (a) && (a) < (b))

struct bitset
{
  size_t size;
  uint8_t bits[]; // Cool C99 trick
};

bitset_t *bs_new(size_t siz)
{
  bitset_t *b = calloc(1, siz + sizeof(size_t));
  if (b)
    {
      b->size = siz;
    }
  return b;
}

void bs_free(bitset_t *b)
{
  free(b);
}

bool bs_contains(bitset_t *b, size_t v)
{
  Index_check(v, b->size / 8);

  return b->bits[v / 8] & On(v % 8);
}

void bs_set(bitset_t *b, size_t v)
{
  Index_check(v, b->size / 8);

  b->bits[v / 8] |= On(v % 8);
}

void bs_unset(bitset_t *b, size_t v)
{
  Index_check(v, b->size / 8);

  b->bits[v / 8] &= Off(v % 8);
}

int main(int argc, char *argv[])
{
  bitset_t *b = bs_new(1024 * 1024);

  while (*++argv)
    {
      switch (**argv)
        {
        case '+':
          {
	    size_t v = atol(*argv+1);
	    printf("Adding %zd to the set\n", v);
	    bs_set(b, v);
	    break;
	  }
        case '-':
          {
	    size_t v = atol(*argv+1);
	    printf("Removing %zd from the set\n", v);
	    bs_unset(b, v);
	    break;
	  }
        default:
          {
	    size_t v = atol(*argv);
	    printf("The set %s the value %zd\n", bs_contains(b, v) ? "contains" : "does not contain", v);
	  }
        }
    }

  printf("%d\n", INT_MAX);
  bs_free(b);
  return 0;
}
