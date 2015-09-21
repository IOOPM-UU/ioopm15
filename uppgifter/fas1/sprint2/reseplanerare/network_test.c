#include <CUnit/Basic.h>
#include "network.h"
#include <stdlib.h>
#include <assert.h>

static network_t *network;

int init_suite(void)
{
    FILE *f = fopen("data.txt", "r");
    network = network_parse(f);
    fclose(f);
    return 0;
}

int clean_suite(void)
{
    network_free(network);

    return 0;
}

void testFINDTRAVELS(void)
{
    list_t *route = network_find_travels(network, "Allianshallen", "Nymansgatan");
    CU_ASSERT(route && "route must exist");
    travel_t *bus28;
    CU_ASSERT_FATAL(list_len(route) == 1 && "route must be direct");
    CU_ASSERT_FATAL(list_nth(route, 0, (void **)&bus28));
    printf("\nbus28@%p->duration=%i / 0x%x\n", bus28, bus28->duration,
           bus28->duration);
    CU_ASSERT_EQUAL(bus28->duration, 7);
    CU_ASSERT_EQUAL(bus28->line, 28);
    CU_ASSERT_STRING_EQUAL(bus28->from_stop, "Allianshallen");
    CU_ASSERT_STRING_EQUAL(bus28->to_stop, "Nymansgatan");
    list_foreach(route, free);
    list_free(route);
}

void testFINDTRAVELS_LONG()
{
    list_t *route = network_find_travels(network, "Varnlundsgatan", "Stora Torget");
    CU_ASSERT(list_len(route) == 1 &&
              "many stops on one line are still only one item");
    list_foreach(route, free);
    list_free(route);
}

void testFINDTRAVELS_SWITCH()
{
    list_t *route = network_find_travels(network, "Timjansgatan", "Ekonomikum");
    CU_ASSERT_EQUAL_FATAL(list_len(route), 2);
    travel_t *bus9, *bus2;
    list_nth(route, 0, (void **)&bus9);
    list_nth(route, 1, (void **)&bus2);

    puts("");
    list_foreach(route, (void_fun_t)travel_print);

    CU_ASSERT_STRING_EQUAL(bus9->from_stop, "Timjansgatan");
    printf("bus9 duration is: 0x%x\n", bus9->duration);
    CU_ASSERT_EQUAL(bus9->duration, 10);
    CU_ASSERT_STRING_EQUAL(bus9->to_stop, "Vaksala torg");
    CU_ASSERT_EQUAL(bus9->line, 9);

    CU_ASSERT_STRING_EQUAL(bus2->from_stop, "Vaksala torg");
    printf("bus2 duration is: %i\n", bus2->duration);
    CU_ASSERT_EQUAL(bus2->duration, 10);
    CU_ASSERT_STRING_EQUAL(bus2->to_stop, "Ekonomikum");
    CU_ASSERT_EQUAL(bus2->line, 2);

    list_foreach(route, free);
    list_free(route);
}

int main(int argc, char const *argv[])
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Network", init_suite, clean_suite);
    if (NULL == pSuite)
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

    if ((!CU_add_test(pSuite, "test of network_find_travels", testFINDTRAVELS)) ||
            (!CU_add_test(pSuite, "test of network_find_travels (longer travel)",
                          testFINDTRAVELS_LONG)) ||
            (!CU_add_test(pSuite, "test of network_find_travels (travel with switch)",
                          testFINDTRAVELS_SWITCH)))
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
