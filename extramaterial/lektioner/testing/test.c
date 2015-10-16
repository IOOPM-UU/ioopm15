#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include "tree.h"
#include "set.h"

#define Setup(n) set_t *s##n = set_new()
#define Teardown(n) set_free(s##n)

void test_new()
{
  Setup();

  CU_ASSERT_FALSE(s == NULL);
  CU_ASSERT_TRUE(set_size(s) == 0);

  Teardown();
}

void test_free()
{
  printf("%s test not implemented yet\n", __func__);
}

void test_add()
{
  printf("%s test not implemented yet\n", __func__);
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
  printf("%s test not implemented yet\n", __func__);
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
  printf("%s test not implemented yet\n", __func__);
}

int main(int argc, char *argv[])
{
  // Initialise
  CU_initialize_registry();

  // Set up suites and tests
  //////////////////////////////////////////////////////////////////////////////
  CU_pSuite cd = CU_add_suite("Test cd and destruction", NULL, NULL);
  CU_add_test(cd, "New", test_new);
  CU_add_test(cd, "Free", test_free);

  //////////////////////////////////////////////////////////////////////////////
  CU_pSuite elems = CU_add_suite("Individual elems", NULL, NULL);
  CU_add_test(elems, "Add", test_add);
  CU_add_test(elems, "Contains", test_contains);

  //////////////////////////////////////////////////////////////////////////////
  CU_pSuite c = CU_add_suite("Consistency", NULL, NULL);
  CU_add_test(c, "Size", test_size);

  //////////////////////////////////////////////////////////////////////////////
  CU_pSuite bops = CU_add_suite("Binary operations", NULL, NULL);
  CU_add_test(bops, "Top", test_union);
  CU_add_test(bops, "Top", test_intersection);
  CU_add_test(bops, "Top", test_subtraction);
  CU_add_test(bops, "Top", test_equal);

  
  // Actually run tests
  //////////////////////////////////////////////////////////////////////////////
  CU_basic_run_tests();

  // Tear down
  //////////////////////////////////////////////////////////////////////////////
  CU_cleanup_registry();

  return 0;
}
