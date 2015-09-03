#include <stdio.h>
#include <string.h>

void strip_newline(char *str)
{
  char *new_line = strchr(str, '\n');
  if (new_line)
    {
      *new_line = '\0';
    }
}

void strip_newline_robust(char *str, size_t len)
{
  for (int i = 0; i < len; ++i)
    {
      switch (str[i])
        {
        case '\n': { str[i] = '\0'; return; }
        case '\0': { return; }
        }
    }
}

int main (void)
{
  char password[] = "abc123";
  size_t entered_size;
  char *entered;

  puts("Please enter the secret code:");
  getline(&entered, &entered_size, stdin); // read input
  strip_newline(entered);

  if (strncmp(entered, password, entered_size) == 0)
    {
      puts("You are logged in!");
    }
  else
    {
      puts("Incorrect password!");
    }

  return 0;
}
