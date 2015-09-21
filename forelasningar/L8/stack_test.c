#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include "stack.h"

void test_stack_creation()
{
  int_stack_t *s = stack_new();

  CU_ASSERT_FALSE(s == NULL);
  CU_ASSERT_TRUE(stack_height(s) == 0);

  stack_free(s); 
}

void test_stack_height()
{
  int_stack_t *s = stack_new();

  CU_ASSERT_TRUE(stack_height(s) == 0);

  stack_push(s, 0);

  CU_ASSERT_TRUE(stack_height(s) == 1);

  stack_push(s, 0);

  CU_ASSERT_TRUE(stack_height(s) == 2);

  stack_pop(s);

  CU_ASSERT_TRUE(stack_height(s) == 1);

  stack_pop(s);

  CU_ASSERT_TRUE(stack_height(s) == 0);

  stack_free(s); 
}

void test_stack_push_pop()
{
  int_stack_t *s = stack_new();
  const int TEST_VALUES[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  for (int i = sizeof(TEST_VALUES) / sizeof(int) - 1; i >= 0; --i)
    {
      stack_push(s, TEST_VALUES[i]);
    }

  for (int i = 0; i < sizeof(TEST_VALUES) / sizeof(int); ++i)
    {
      CU_ASSERT_TRUE(stack_pop(s) == TEST_VALUES[i]);
    }
    
  stack_free(s); 
}

void test_stack_top()
{
  int_stack_t *s = stack_new();

  stack_push(s, 1);

  CU_ASSERT_TRUE(stack_top(s) == 1);

  stack_push(s, 20);

  CU_ASSERT_TRUE(stack_top(s) == 20);

  stack_pop(s);

  CU_ASSERT_TRUE(stack_top(s) == 1);

  stack_free(s); 
}


int main(int argc, char *argv[])
{
  // Initialise
  CU_initialize_registry();

  // Set up suites and tests
  //////////////////////////////////////////////////////////////////////////////
  CU_pSuite creation = CU_add_suite("Test creation and height", NULL, NULL);
  CU_add_test(creation, "Creation", test_stack_creation);
  CU_add_test(creation, "Height", test_stack_height);
  
  //////////////////////////////////////////////////////////////////////////////
  CU_pSuite pushpoptop = CU_add_suite("Test push, pop and top", NULL, NULL);
  CU_add_test(pushpoptop, "Push and pop", test_stack_push_pop);
  CU_add_test(pushpoptop, "Top", test_stack_top);

  // Actually run tests
  //////////////////////////////////////////////////////////////////////////////
  CU_basic_run_tests();

  // Tear down
  //////////////////////////////////////////////////////////////////////////////
  CU_cleanup_registry();

  return 0;
}
