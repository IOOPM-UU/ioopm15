#include "graph.h"
#include "list.h"
#include "stdlib.h"
#include <assert.h>
#include <stdio.h>

typedef void node_t;
typedef struct _graph_edge_t edge_t;
typedef struct _distance_label_t distance_label_t;

struct _graph_edge_t
{
    node_t *from;
    node_t *to;
    void *label;
};

struct _graph_t
{
    list_t *nodes;
    list_t *edges;
    comparator_t comp;
};


struct _distance_label_t
{
    void *label;
    list_t *path;
    int dist;
};


edge_t  *new_edge()
{
    return calloc(1, sizeof(struct _graph_edge_t));
}

graph_t *graph_new(comparator_t comp)
{
    graph_t *ret = calloc(1, sizeof(struct _graph_t));

    ret->nodes = list_new();
    ret->edges = list_new();
    ret->comp = comp;

    return ret;
}

bool graph_add_node(graph_t *g, void *label)
{
    if (list_has(g->nodes, g->comp, label))
        {
            return false;
        }
    else
        {
            list_add(g->nodes, label);
            return true;
        }
}

bool graph_has_node(graph_t *g, void *label)
{
    return list_has(g->nodes, g->comp, label);
}

void graph_foreach_node(graph_t *g, void_fun_t f)
{
    list_foreach(g->nodes, f);
}

void graph_foreach_edge(graph_t *g, void_fun3_t f)
{
    iter_t *it;
    for (it = iter(g->edges); !iter_done(it); iter_next(it))
        {
            edge_t  *e = iter_get(it);
            f(e->from, e->to, e->label);
        }
    iter_free(it);
}

bool graph_add_edge(graph_t *g, void *from, void *to, void *label)
{
    assert(list_has(g->nodes, g->comp, from) && list_has(g->nodes, g->comp, to));
    edge_t  *e = new_edge();
    e->from = from;
    e->to = to;
    e->label = label;
    list_add(g->edges, e);
    return true;
}

bool graph_has_edge(graph_t *g, void *from, void *to, void **label)
{
    iter_t *it;
    for (it = iter(g->edges); !iter_done(it); iter_next(it))
        {
            edge_t  *e = iter_get(it);
            if ((g->comp(from, e->from) && g->comp(to, e->to)) || (g->comp(from, e->to) && g->comp(to, e->from)))
                {
                    *label = e->label;
                    iter_free(it);
                    return true;
                }
        }
    *label = NULL;
    iter_free(it);
    return false;
}

list_t *graph_find_neighbors(graph_t *g, void *node)
{
    list_t *ret = list_new();
    iter_t *eit;
    for (eit = iter(g->edges); !iter_done(eit); iter_next(eit))
        {
            edge_t  *e = iter_get(eit);
            if (g->comp(e->from, node))
                {
                    list_add(ret, e->to);
                }
            else if (g->comp(e->to, node))
              {
                    list_add(ret, e->from);
              }
        }
    iter_free(eit);
    return ret;
}

distance_label_t *get_distance_label(list_t *distanceLabels, void *lbl,
                                     comparator_t comp)
{
    assert(distanceLabels);
    assert(lbl);
    assert(comp);
    iter_t *dliter;
    for (dliter = iter(distanceLabels); !iter_done(dliter); iter_next(dliter))
        {
            distance_label_t *dl = iter_get(dliter);
            if (comp(dl->label, lbl))
                {
                    // printf("Did find distance label for %s: path is: %p\n", lbl, dl->path);

                    iter_free(dliter);
                    return dl;
                }
        }
    // printf("did not find distance label for %s\n", lbl);
    iter_free(dliter);
    return NULL;
}

void *get_min_distance_node(list_t *distanceLabels, comparator_t comp,
                            list_t *visited)
{
    assert(distanceLabels);

    int minDist = -1;
    void *minLabel = NULL;
    iter_t *it;
    for (it = iter(distanceLabels); !iter_done(it); iter_next(it))
        {
            distance_label_t *itdl = iter_get(it);
            if (itdl->dist == -1)
                {
                    continue;
                }
            if (list_has(visited, comp, itdl->label))
                {
                    continue;
                }
            if (minDist == -1 || itdl->dist < minDist)
                {
                    minDist = itdl->dist;
                    minLabel = itdl->label;
                }
        }
    iter_free(it);
    return minLabel;
}

void update_distance(list_t *distanceLabels, void *lbl, comparator_t comp,
                     int tentativeDist, list_t *tentativePath)
{
    assert(distanceLabels);
    assert(lbl);
    assert(comp);
    assert(tentativePath);
    distance_label_t *dl = get_distance_label(distanceLabels, lbl, comp);
    assert(dl);
    if ((dl->dist == -1) || (dl->dist > tentativeDist))
        {
            dl->dist = tentativeDist;
            if (dl->path)
                {
                    list_free(dl->path);
                }
            dl->path = tentativePath;
        }
    else
        {
            list_free(tentativePath);
        }
}

list_t *unvisited_neighbors(graph_t *g, void *current, list_t *visited)
{
    list_t *neighs = graph_find_neighbors(g, current);

    list_t *unvisited_neighs = list_new();
    iter_t *nit;
    for (nit = iter(neighs); !iter_done(nit); iter_next(nit))
        {
            void *neigh = iter_get(nit);
            if (!list_has(visited, g->comp, neigh))
                {
                    list_add(unvisited_neighs, neigh);
                }
        }
    iter_free(nit);
    list_free(neighs);
    return unvisited_neighs;
}

void dijkstra(graph_t *g, void *current, void *to, list_t *visited,
              list_t *distanceLabels)
{
    assert(g);
    assert(current);
    assert(to);
    assert(visited);
    assert(distanceLabels);
    while (true)
        {
            if (!list_has(visited, g->comp, current))
                {

                    list_t *unvisited_neighs = unvisited_neighbors(g, current, visited);
                    distance_label_t *here =
                        get_distance_label(distanceLabels, current, g->comp);

                    iter_t *it;
                    for (it = iter(unvisited_neighs); !iter_done(it); iter_next(it))
                        {
                            void *neigh = iter_get(it);
                            list_t *tentativePath = list_clone(here->path);
                            list_add(tentativePath, neigh);
                            update_distance(distanceLabels, neigh, g->comp, here->dist + 1,
                                            tentativePath);
                        }
                    iter_free(it);
                }
            list_add(visited, current);

            if (g->comp(current, to))
                {
                    return;
                }

            current = get_min_distance_node(distanceLabels, g->comp, visited);
            assert(current);
        }
}

list_t *graph_find_path(graph_t *g, void *from, void *to)
{
    assert(graph_has_node(g, from) && graph_has_node(g, to));
    list_t *visited = list_new();
    list_t *distanceLabels = list_new();
    iter_t *it;
    for (it = iter(g->nodes); !iter_done(it); iter_next(it))
        {
            distance_label_t *dl = calloc(1, sizeof(distance_label_t));
            dl->dist = -1;
            dl->label = iter_get(it);
            dl->path = NULL;
            list_add(distanceLabels, dl);
        }
    iter_free(it);
    get_distance_label(distanceLabels, from, g->comp)->path = list_new();
    dijkstra(g, from, to, visited, distanceLabels);
    list_t *best = get_distance_label(distanceLabels, to, g->comp)->path;
    assert(best);
    list_foreach(distanceLabels, free);
    list_free(distanceLabels);
    list_free(visited);
    return best;
}

void graph_print(graph_t *g)
{
    int nsize = list_len(g->nodes);
    int esize = list_len(g->edges);

    for (size_t i = 0; i < nsize; ++i)
        {
            node_t **n;
            list_nth(g->nodes, i, (void **)&n);
        }
    for (size_t i = 0; i < esize; ++i)
        {
            edge_t  *e;
            list_nth(g->edges, i, (void **)&e);
        }
}

void graph_free(graph_t *g)
{
    list_free(g->nodes);
    list_free(g->edges);
}
