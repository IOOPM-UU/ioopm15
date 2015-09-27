#include <stdio.h>
#include <string.h>

void strip_newline(char *str)
{
  char *new_line = strchr(str, '\n'); // Finns \n i strängen...?
  if (new_line)
    {
      *new_line = '\0'; // ...i så fall, ersätt med \0
    }
}

// En variant av funktionen ovan som också tar en maxlängd
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
  size_t entered_size = 0;
  char *entered = NULL;

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

  free(entered); 

  return 0;
}
