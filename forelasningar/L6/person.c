#include <stdlib.h>

#include "person.h"

struct person{
  char *first;
  char *last;
};

struct person *buildPerson(char *first, char *last){
  struct person *p = malloc(sizeof(struct person));
  if(!p)
    {
      return NULL;
    }
  p->first = first;
  p->last = last;
  return p;
}

char *getFirstName(struct person *p){
  return p->first;
}

char *getLastName(struct person *p){
  return p->last;
}