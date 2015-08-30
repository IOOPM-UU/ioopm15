#include <stdio.h>

int main()
{
  char buffer[128];
  int age;
  puts("What is your name?");
  scanf("%s", buffer);
  puts("How old are you?");
  while(scanf("%d", &age) == 0){
    puts("Please use digits");
    while(getchar() != '\n');
  }
  printf("Hello %s! You are looking good (for a %d year old)!\n", 
         buffer, age);
  return 0;
}