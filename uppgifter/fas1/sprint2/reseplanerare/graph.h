/** \file graph.h

  \brief A generic graph implementation.

  A directed graph with support for node- and edge-labels and
  path-finding. */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "util.h"
#include "list.h"

/**
  \typedef An opaque
*/
typedef struct _graph_t graph_t;

/**

  Allocate a new graph.

  \param comp a side effect-free function that is defines whether or
  not nodes and edge labels are equal.

  \returns an empty graph

*/
graph_t* graph_new(comparator_t comp);

/**

  Add a node to a graph.

  The graph_t * will never deallocate a node. You can deallocate all graph
  nodes using a call like `graph_foreach_node(free)` (substituting
  your own deallocation function for `free` where necessary).

  \param node A node to add.

  \sa graph_foreach_node

*/
bool graph_add_node(graph_t *, void *node);

/**

  Test whether a node is in the graph.

  \param node The node we are looking for.

  \returns true if there is a node for which the comparator (see \ref
  graph_new)

*/
bool graph_has_node(graph_t *, void *node);

/**

  Run a function with each of the graph's nodes as input.

  \param fun A function to run once with each node as argument.

  \sa graph_foreach_edge

*/
void graph_foreach_node(graph_t *, void_fun_t fun);

/**
  Run a function with each of the graph's edges as input.

  Runs the function with each of the graph's edge labels, as well as
  the start- and the end-node of the edge as input. The function will
  be called with arguments in this order: `fun(from, to, edge_label)`.

  \param fun A function to run once for each edge.

  \sa graph_foreach_node

*/
void graph_foreach_edge(graph_t *, void_fun3_t fun);

/**

  Add an edge to a graph.

  \param from The starting node of the edge.

  \param to The end node of the edge.

  \param label The label (might be `NULL`) of the edge.

  \warning Adding an
  edge between node that are not in the graph is undefined behaviour

*/
bool graph_add_edge(graph_t *, void *from, void *to, void *label);

/**

  Test whether there is an edge between two nodes.

  \param from The starting node.

  \param to The end node.

  \param label *label will be set to the edge label if an edge exists,
  to `NULL` otherwise.

  \returns `true` if an edge exists, `false` otherwise.

*/
bool graph_has_edge(graph_t *, void *from, void *to, void **label);

/**

  Find all direct neighbors of a node.

  \param node The node whose neighbors are queried.

  \returns A list containing ALL direct neighbors of a node in a
  graph.

  \warning If the node is not in the graph, behaviour is undefined.

*/
list_t *graph_find_neighbors(graph_t *, void *node);

/**

  Find a path between two nodes.

  The path will be a shortest path, assuming equal weights for all
  nodes.

  \returns A list of nodes (not including the starting node but
  including the goal node) if a path exists; `NULL` otherwise.

*/
list_t *graph_find_path(graph_t *, void *from, void *to);

/**

  Deallocate all memory alloceted by the graph.

  Does not cover nodes and edge labels.

*/
void graph_free(graph_t *);

#endif // GRAPH_H
