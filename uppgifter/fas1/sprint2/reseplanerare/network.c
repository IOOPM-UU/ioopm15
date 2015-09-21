#include "network.h"
#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "util.h"

struct _network_t
{
    graph_t *g;
};

typedef struct _edge_t edge_t;

struct _edge_t
{
    int duration;
    line_no line;
};

#define BUFSIZE 1000

void trim_leading_space(char *dest, const char *src)
{
    assert(dest);
    assert(src);
    while (isspace(*src))
        {
            ++src;
        }
    strcpy(dest, src);
}

void printEdge(void *from, void *to, void *label)
{
    edge_t *e = label;
    printf("#%2i:%30s --(%2imin)--> %s\n", e->line, (char *)from, e->duration,
           (char *)to);
    // assert(false);
}

network_t *network_parse(FILE *file)
{
    assert(file);
    network_t *netw = calloc(1, sizeof(struct _network_t));
    netw->g = graph_new(streq);

    char buffer[BUFSIZE];
    while (fgets(buffer, BUFSIZE, file))
        {
            char bus_from[BUFSIZE];
            char bus_to[BUFSIZE];

            edge_t *e = malloc(sizeof(struct _edge_t));

            sscanf(strtok(buffer, ","), "%i", &(e->line));
            trim_leading_space(bus_from, strtok(NULL, ","));
            trim_leading_space(bus_to, strtok(NULL, ","));
            sscanf(strtok(NULL, ","), "%i", &(e->duration));

            puts("adding edge...");
            printEdge(bus_from, bus_to, &(e->duration));

            assert(e->duration > 0 && e->duration < 100);

            char *bus_from_dup = strdup(bus_from);
            char *bus_to_dup = strdup(bus_to);

            graph_add_node(netw->g, bus_from_dup);
            graph_add_node(netw->g, bus_to_dup);
            graph_add_edge(netw->g, bus_from_dup, bus_to_dup, e);
        }

    return netw;
}

void network_print(network_t *n)
{
    assert(n);
    graph_foreach_edge(n->g, printEdge);
}

travel_t *travel_clone(travel_t *orig)
{
    travel_t *clone = malloc(sizeof(travel_t));
    clone->from_stop = orig->from_stop;
    clone->from_time = orig->from_time;
    clone->line = orig->line;
    clone->to_stop = orig->to_stop;
    clone->duration = orig->duration;
    return clone;
}

void travel_print(travel_t *travel)
{
    printf("@ %i: #%i %s --(%i)--> %s\n", travel->from_time, travel->line,
           travel->from_stop, travel->duration, travel->to_stop);
}

list_t *merge_rides(list_t *route)
{
    list_t *ret = list_new();
    if (list_len(route) == 1)
        {
            travel_t *travel;
            list_nth(route, 0, (void **)&travel);
            list_add(ret, travel_clone(travel));
        }
    else if (list_len(route) != 0)
        {
            travel_t *travel;
            list_nth(route, 0, (void **)&travel);

            travel_t *merged = travel_clone(travel);

            iter_t *it = iter(route);
            iter_next(it); // we already took care of the first
            for (; !iter_done(it); iter_next(it))
                {
                    travel = iter_get(it);

                    if (travel->line == merged->line)
                        {
                            merged->duration += travel->duration;
                            merged->to_stop = travel->to_stop;
                        }
                    else
                        {
                            list_add(ret, merged);
                            merged = travel_clone(travel);
                        }
                }
            iter_free(it);
            list_add(ret, merged);
        }

    return ret;
}

list_t *network_find_travels(network_t *n, char *from, char *to)
{
    assert(n && from && to);
    if (streq(from, to))
        {
            return list_new();
        }

    list_t *ret = list_new();

    list_t *path = graph_find_path(n->g, from, to);
    char *last_stop = from;
    iter_t *it;
    for (it = iter(path); !iter_done(it); iter_next(it))
        {
            travel_t *travel = calloc(1, sizeof(travel_t));
            edge_t *e;
            bool has = graph_has_edge(n->g, last_stop, iter_get(it), (void **)&e);
            assert(has);
            printf("\nadding duration to travel@%p: %i\n", travel, e->duration);
            travel->duration = e->duration;
            travel->from_stop = last_stop;
            travel->from_time = -1; // FIXME
            travel->line = e->line;
            travel->to_stop = iter_get(it);
            list_add(ret, travel);

            last_stop = iter_get(it);
        }
    iter_free(it);

    list_t *merged = merge_rides(ret);
    list_foreach(ret, free);

    return merged;
}

void free_edge_label(void *from, void *to, void *label)
{
    free(label);
}

void network_free(network_t *n)
{
    graph_foreach_edge(n->g, free_edge_label);
    graph_foreach_node(n->g, free);
    graph_free(n->g);
    free(n);
}
