#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      puts("Usage: ./mygrep <pattern> <name>");
    }
  else
    {
      FILE *f = fopen(argv[2], "r");
      int str_len;
      size_t buf_siz;
      char *string; 
      char *pattern = argv[1];
      
      while ((str_len = getline(&string, &buf_siz, f)) > 0)
	{
	  if (strnstr(string, pattern, str_len))
	    printf("%s", string);
	}

      fclose(f);
    }
  return 0; 
}
