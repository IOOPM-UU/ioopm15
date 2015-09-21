/**
  \file network.h
  \brief Functions for route planning.

  This module is a thin wrapper around a generic graph implementation.
  It adds the ability to parse transportation networks from a \ref
  FILE*, and to find travels.

*/

#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include "list.h"

/**
   An opaque type for a transportation network.
*/
typedef struct _network_t network_t;

typedef int time;

typedef int line_no;

typedef struct travel travel_t;

/**
  One leg of a travel.

  \sa The ::network_find_travels function returns a list of such travels.
*/
struct travel
{
    char *from_stop;
    time from_time;
    char *to_stop;
    int duration;
    line_no line;
};

/**
 Parse a network from a file. The function expects an open file and
 will not close the file for you.
*/
network_t *network_parse(FILE *file);

/**
  Prints a version of the network to stdout. For debugging purposes
  only.
*/
void network_print(network_t *);

/**
  Takes a travel and prints it to stdout. For debugging purposes only.
*/
void travel_print(travel_t *);

/**
  Finds a travel from one stop to another.

  \returns
    - NULL or an empty list if there is no such travel.
    - A list containing Travels, otherwise
*/
list_t *network_find_travels(network_t *n, char *from, char *to);

/**
  Frees a network and all the data it allocated.
*/
void network_free(network_t *);

#endif // NETWORK_H
