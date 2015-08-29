#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      puts("Usage: ./mycat <name>");
    }
  else
    {
      FILE *f = fopen(argv[1], "r");
      int c = 0; 
      while ((c = fgetc(f)) != EOF)
	{
	  putchar(c);
	}
    }
  return 0; 
}
