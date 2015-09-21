#include <CUnit/Basic.h>
#include "list.h"
#include <assert.h>
#include <stdlib.h>

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void testCREATEFREE()
{
    list_free(list_new());
}

void testCREATEEMPTY()
{
    list_t *l = list_new();
    CU_ASSERT_EQUAL(list_len(l), 0);
    list_free(l);
}

void testLENGTH()
{
    list_t *l = list_new();
    for (int i = 0; i < 100; ++i)
        {
            CU_ASSERT_EQUAL(list_len(l), i);
            list_add(l, malloc(sizeof(int)));
        }

    list_foreach(l, free);
    list_free(l);
}

void testITER_GET()
{
    list_t *l = list_new();
    for (int i = 0; i < 3; ++i)
        {
            int *x = malloc(sizeof(int));
            *x = i;
            list_add(l, x);
        }

    iter_t *it = iter(l);
    int *first = iter_get(it);
    CU_ASSERT_EQUAL(*first, 0);
    iter_free(it);

    list_foreach(l, free);
    list_free(l);
}

void testITERATION()
{
    list_t *l = list_new();
    for (int i = 0; i < 3; ++i)
        {
            int *x = malloc(sizeof(int));
            *x = i;
            list_add(l, x);
        }

    int count = 0;
    iter_t *it;
    for (it = iter(l); !iter_done(it); iter_next(it))
        {
            count++;
        }
    iter_free(it);
    CU_ASSERT_EQUAL(count, list_len(l));

    list_foreach(l, free);
    list_free(l);
}

void testNTH()
{
    list_t *l = list_new();
    for (int i = 0; i < 100; ++i)
        {
            int *x = malloc(sizeof(int));
            *x = i;
            list_add(l, x);
        }

    int *x;

    for (int i = 0; i < 100; ++i)
        {
            CU_ASSERT(list_nth(l, i, (void **)&x));
            CU_ASSERT_EQUAL(*x, i);
        }

    CU_ASSERT_FALSE(list_nth(l, -1, (void **)&x));
    CU_ASSERT_EQUAL(x, NULL);
    CU_ASSERT_FALSE(list_nth(l, 100, (void **)&x));
    CU_ASSERT_EQUAL(x, NULL);

    list_foreach(l, free);
    list_free(l);
}

void testLISTHAS()
{
    list_t *l = list_new();
    list_add(l, strdup("hello"));
    list_add(l, strdup("world"));

    CU_ASSERT_FALSE(list_has(l, streq, "HELLO"));
    CU_ASSERT(list_has(l, streq, "hello"));

    list_foreach(l, free);
    list_free(l);
}

int main(int argc, char const *argv[])
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("list_t *", init_suite, clean_suite);
    if (NULL == pSuite)
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

    if ((NULL == CU_add_test(pSuite, "test of list_create and list_free",
                             testCREATEFREE)) ||
            (NULL ==
             CU_add_test(pSuite, "test that new list is empty", testCREATEEMPTY)) ||
            (NULL == CU_add_test(pSuite, "test list_len function", testLENGTH)) ||
            (NULL == CU_add_test(pSuite, "test list_nth function", testNTH)) ||
            (NULL == CU_add_test(pSuite, "test list_has function", testLISTHAS)) ||
            (NULL ==
             CU_add_test(pSuite, "test getting first element", testITER_GET)) ||
            (NULL == CU_add_test(pSuite, "test list iteration", testITERATION)))
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int failures = CU_get_number_of_failures();
    CU_cleanup_registry();

    assert(failures == 0);
    return EXIT_SUCCESS;
}
