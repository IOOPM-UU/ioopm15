#include<stdio.h>
#include<stdlib.h>

struct point {
  int x; 
  int y;
};
typedef struct point *Point;

void translate(Point p, Point relative) {
  p->x = p->x + relative->x; // alternativt p->x += relative->x 
  p->y = p->y + relative->y;
}

void printPoint(char* msg, Point p) {
  printf("%s (%d,%d)\n", msg, p->x, p->y);
}

int main(void) {
  Point somewhere = malloc(sizeof(struct point));
  somewhere->x = 7; 
  somewhere->y = 3; 
  Point other     = malloc(sizeof(struct point));
  other->x = 4;
  other->y = 5;
  printPoint("Somewhere: ", somewhere);
  printPoint("Other:     ", other);
  translate(somewhere, other);
  printPoint("Somewhere translated by other", somewhere);
  return 0;
}
