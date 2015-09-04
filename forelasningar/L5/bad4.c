#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
  char *first_name;
  char *last_name;
  int age;
  struct person *spouse;
};

void marry(struct person *p1, struct person *p2)
{
  static char *music[] = { "Godländsk sommarnatt på trumpet", "Tannenbaum på pianola", "Sked" };
  
  printf("\n%s...\n", music[rand() % 3]); 

  p1->last_name = p2->last_name;
  p1->spouse = p2;
  p2->spouse = p1;
}

void print_person(struct person *p)
{
  printf("%s, %s is %d years old", p->last_name, p->first_name, p->age);
  if (p->spouse)
    {
      printf(" and married to %s (age %d).", p->spouse->first_name, p->spouse->age);
    }
  printf("\n");
}

int main(int argc, char *argv[])
{
  if (argc < 7)
    {
      printf("Usage: ./%s first1 last1 age1 first2 last2 age2", argv[0]);
    }
  else
    {
      // Construct p1 from the command line arguments 
      struct person p1 = {
	.first_name = argv[1], // note, no strdup (cf. bad3.c)
	.last_name  = argv[2],
	.age        = atoi(argv[3])
      };

      struct person p2 = {
	.first_name = argv[4],
	.last_name  = argv[5],
	.age        = atoi(argv[6])
      };

      // Print the two singles
      print_person(&p1);
      print_person(&p2);

      // Next line just initialises the random function used in marry
      srand(p2.age);

      // Marry p1 and p2 
      marry(&p1, &p2);

      // Print the two spouses
      print_person(&p1);
      print_person(&p2);

      free(p1->last_name);
      free(p2->last_name);
      free(p1->first_name);
      free(p2->first_name);
      free(p1);
      free(p2);
    }

  return 0;
}
