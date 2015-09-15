#include <stdio.h>

#include "asker.h"
#include "person.h"

int main(void)
{
  char *first = askString("What is your first name?");
  char *last = askString("What is your last name?");
  struct person *p = buildPerson(first, last);
  printf("Greetings %s of the glorious %s family!!\n",
         getFirstName(p), getLastName(p));
  // TODO: Free the memory allocated for the person!
  return 0;
}
