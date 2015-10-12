#include "tree.h"
#include "set.h"
#include <assert.h>

#define Setup(n) set_t *s##n = set_new()
#define Teardown(n) set_free(s##n)
#define Passed() printf("%s PASSED\n", __func__)

void test_new()
{
  printf("%s test not implemented yet\n", __func__);
}

void test_free()
{
  printf("%s test not implemented yet\n", __func__);
}

void test_add()
{
  Setup();

  assert(set_size(s) == 0);
  set_add(s, 3);
  assert(set_size(s) == 1);
  set_add(s, 5);
  assert(set_size(s) == 2);
  set_add(s, 7);
  assert(set_size(s) == 3);
  set_add(s, 7);
  assert(set_size(s) == 3);
  
  Teardown();
  Passed();
}

void test_size()
{
  printf("%s test not implemented yet\n", __func__);
}

void test_contains()
{
  printf("%s test not implemented yet\n", __func__);
}

void test_union()
{
  printf("%s test not implemented yet\n", __func__);
}

void test_intersection()
{
  Setup(1);
  Setup(2);

  set_add(s1, 1);
  set_add(s1, 2);
  set_add(s1, 3);

  set_add(s2, 1);
  set_add(s2, 2);
  set_add(s2, 3);

  set_t *s3 = set_intersection(s1, s2);
  assert(set_size(s3) == 3);
  set_free(s3);
  
  Teardown(1);
  Teardown(2);
  Passed();
}

void test_subtraction()
{
  printf("%s test not implemented yet\n", __func__);
}

void test_print()
{
  printf("%s test not implemented yet\n", __func__);
}

void test_equal()
{
  Setup(1);
  Setup(2);

  set_add(s1, 2);
  set_add(s1, 3);
  set_add(s1, 1);

  set_add(s2, 1);
  set_add(s2, 3);
  set_add(s2, 2);

  assert(set_equal(s1, s2));
  
  Teardown(1);
  Teardown(2);
  Passed();
}

int main(int argc, char *argv[])
{
  test_new();
  test_free();
  test_add();
  test_size();
  test_contains();
  test_union();
  test_intersection();
  test_subtraction();
  test_print();
  test_equal();
  return 0;
}
