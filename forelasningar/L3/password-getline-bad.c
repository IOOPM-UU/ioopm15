#include <stdio.h>

int main (void)
{
  char password[] = "abc123";
  size_t entered_size;
  char *entered;

  puts("Please enter the secret code:");
  getline(&entered, &entered_size, stdin); // read input

  if (entered == password)
    {
      puts("You are logged in!");
    }
  else
    {
      puts("Incorrect password!");
    }

  return 0;
}
