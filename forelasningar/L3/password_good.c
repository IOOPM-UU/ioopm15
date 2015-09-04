#include <stdio.h>
#include <string.h>

int main (void)
{
  int MAX_LEN = 128;
  char password[] = "abc123";
  char entered[MAX_LEN];
  size_t entered_size; // längden på entered

  puts("Please enter the secret code:");
  scanf("%s", entered); // read input
  entered_size = strlen(entered);

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