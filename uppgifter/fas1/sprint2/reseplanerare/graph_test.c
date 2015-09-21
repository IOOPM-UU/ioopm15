#include <CUnit/Basic.h>
#include "graph.h"
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
    graph_free(graph_new(streq));
}

graph_t *mkGraphABCDE()
{
    graph_t *g = graph_new(streq);
    graph_add_node(g, strdup("A"));
    graph_add_node(g, strdup("B"));
    graph_add_node(g, strdup("C"));
    graph_add_node(g, strdup("D"));
    graph_add_node(g, strdup("E"));
    return g;
}

void freeGraphABCDE(graph_t *g)
{
    graph_foreach_node(g, free);
    graph_free(g);
}

void testADDEDGE()
{
    graph_t *g = mkGraphABCDE();
    graph_add_edge(g, "A", "B", NULL);
    freeGraphABCDE(g);
}

void testHASNODE()
{
    graph_t *g = mkGraphABCDE();
    CU_ASSERT(graph_has_node(g, "A"));
    freeGraphABCDE(g);
}

void testFINDNEIGHBORS()
{
    graph_t *g = mkGraphABCDE();

    graph_add_edge(g, "A", "B", NULL);

    list_t *neighs = graph_find_neighbors(g, "A");

    CU_ASSERT(list_has(neighs, streq, "B"))
    CU_ASSERT(list_len(neighs) == 1);
    list_free(neighs);

    // adding an additional neighbor:
    graph_add_edge(g, "A", "C", NULL);
    neighs = graph_find_neighbors(g, "A");
    CU_ASSERT(list_has(neighs, streq, "B"));
    CU_ASSERT(list_has(neighs, streq, "C"));
    CU_ASSERT(list_len(neighs) == 2);
    list_free(neighs);

    // the graph is directed:
    graph_add_edge(g, "C", "A", NULL);
    neighs = graph_find_neighbors(g, "A");
    CU_ASSERT(list_has(neighs, streq, "B"));
    CU_ASSERT(list_has(neighs, streq, "C"));
    CU_ASSERT(list_len(neighs) == 2);
    list_free(neighs);

    // add an unrelated edge
    graph_add_edge(g, "D", "E", NULL);
    neighs = graph_find_neighbors(g, "A");
    CU_ASSERT(list_has(neighs, streq, "B"));
    CU_ASSERT(list_has(neighs, streq, "C"));
    CU_ASSERT(list_len(neighs) == 2);
    list_free(neighs);

    freeGraphABCDE(g);
}

void testEDGELABELS()
{
    graph_t *g = mkGraphABCDE();
    graph_add_edge(g, "A", "B", "AB");
    graph_add_edge(g, "B", "C", "BC");
    graph_add_edge(g, "A", "D", "AD");

    void *label;

    CU_ASSERT_FALSE(graph_has_edge(g, "A", "A", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT(graph_has_edge(g, "A", "B", &label));
    CU_ASSERT(streq(label, "AB"));
    CU_ASSERT_FALSE(graph_has_edge(g, "A", "C", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT(graph_has_edge(g, "A", "D", &label));
    CU_ASSERT(streq(label, "AD"));
    CU_ASSERT_FALSE(graph_has_edge(g, "A", "E", &label));
    CU_ASSERT(label == NULL);

    CU_ASSERT_FALSE(graph_has_edge(g, "B", "A", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "B", "B", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT(graph_has_edge(g, "B", "C", &label));
    CU_ASSERT(streq(label, "BC"));
    CU_ASSERT_FALSE(graph_has_edge(g, "B", "D", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "B", "E", &label));
    CU_ASSERT(label == NULL);

    CU_ASSERT_FALSE(graph_has_edge(g, "C", "A", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "C", "B", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "C", "C", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "C", "D", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "C", "E", &label));
    CU_ASSERT(label == NULL);

    CU_ASSERT_FALSE(graph_has_edge(g, "D", "A", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "D", "B", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "D", "C", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "D", "D", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "D", "E", &label));
    CU_ASSERT(label == NULL);

    CU_ASSERT_FALSE(graph_has_edge(g, "E", "A", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "E", "B", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "E", "C", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "E", "D", &label));
    CU_ASSERT(label == NULL);
    CU_ASSERT_FALSE(graph_has_edge(g, "E", "E", &label));
    CU_ASSERT(label == NULL);

    freeGraphABCDE(g);
}

void _puts(char *str)
{
    puts(str);
}

void testFINDPATH()
{
    graph_t *g = mkGraphABCDE();
    graph_add_edge(g, "A", "B", NULL);
    graph_add_edge(g, "B", "C", NULL);
    graph_add_edge(g, "C", "D", NULL);
    graph_add_edge(g, "A", "E", NULL);
    list_t *path = graph_find_path(g, "A", "D");

    void *n0, *n1, *n2;
    CU_ASSERT(list_nth(path, 0, &n0) && streq(n0, "B"));
    CU_ASSERT(list_nth(path, 1, &n1) && streq(n1, "C"));
    CU_ASSERT(list_nth(path, 2, &n2) && streq(n2, "D"));
    list_free(path);

    // now we add a shortcut and try again:
    graph_add_edge(g, "A", "D", NULL);
    path = graph_find_path(g, "A", "D");
    CU_ASSERT(list_nth(path, 0, &n0) && streq(n0, "D") && list_len(path) == 1);
    list_free(path);

    // now we add a cycle and try again:
    graph_add_edge(g, "D", "A", NULL);
    path = graph_find_path(g, "A", "D");
    CU_ASSERT(list_nth(path, 0, &n0) && streq(n0, "D") && list_len(path) == 1);
    list_free(path);

    freeGraphABCDE(g);
}

int main(int argc, char const *argv[])
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("graph_t *", init_suite, clean_suite);
    if (NULL == pSuite)
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

    if ((NULL == CU_add_test(pSuite, "test of graph_create and graph_free",
                             testCREATEFREE)) ||
            (NULL == CU_add_test(pSuite, "test of graph_add_edge", testADDEDGE)) ||
            (NULL == CU_add_test(pSuite, "test of graph_has_node", testHASNODE)) ||
            (NULL == CU_add_test(pSuite, "test of graph_find_neighbors",
                                 testFINDNEIGHBORS)) ||
            (NULL == CU_add_test(pSuite, "test of graph_find_path", testFINDPATH)) ||
            (NULL == CU_add_test(pSuite, "test of edge labels", testEDGELABELS)))
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
