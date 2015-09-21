#include "network.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

#define BUFFER_SIZE 256

void readline(char buffer[], size_t n, FILE *stream)
{
    fgets(buffer, n, stream);
    *strchr(buffer, '\n') = '\0';
}

int main(int argc, char const *argv[])
{
    network_t *n = network_parse(fopen("data.txt", "r"));
    char from[BUFFER_SIZE];
    char to[BUFFER_SIZE];
    puts("================================");
    puts(" Welcome to the travel planner! ");
    puts("================================");
    puts("");
    while(true)
        {
            puts("What is your starting station?");
            readline(from, BUFFER_SIZE, stdin);
            if(from[0] == '\0')
                {
                    break;
                }
            puts("Where would you like to go?");
            readline(to, BUFFER_SIZE, stdin);
            list_t *travels = network_find_travels(n, from, to);
            list_foreach(travels, (void_fun_t)travel_print);
        }
    puts("Good bye!");
//  network_print(n);
    return 0;
}