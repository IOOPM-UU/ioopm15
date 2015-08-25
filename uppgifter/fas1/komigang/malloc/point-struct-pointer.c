#include<stdio.h>

struct point {
  int x; 
  int y;
};

void translate(struct point *p, struct point *relative) {
  p->x = p->x + relative->x; // alternativt p->x += relative->x 
  p->y = p->y + relative->y;
}

void printPoint(char* msg, struct point p) {
  printf("%s (%d,%d)\n", msg, p.x, p.y);
}

int main(void) {
  struct point somewhere = { .x = 7, .y = 3 };
  struct point other     = { .x = 4, .y = 5 };
  printPoint("Somewhere: ", somewhere);
  printPoint("Other:     ", other);
  translate(&somewhere, &other);
  printPoint("Somewhere translated by other", somewhere);
  return 0;
}
