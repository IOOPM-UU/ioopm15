#include <stdio.h>

typedef struct point point_t;

struct point
{
  int x, y;
};

void print_point(point_t p)
{
  printf("(%d,%d)\n", p.x, p.y);
}

void move_point(point_t *p, int dx, int dy)
{
  p->x += dx;
  p->y += dy; 
}

int main(void) {
  point_t p = { .x = 100, .y = 50 }; // Valitt, men felbenäget!
  print_point(p);
  move_point(&p, 10, 10);
  print_point(p);
  return 0;
}
