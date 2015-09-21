#include "stdbool.h"
#include <string.h>
#include <stdio.h>

bool streq(const void *a, const void *b)
{
    return (0 == strcmp((const char *)a, (const char *)b));
}

void printstr(void *str)
{
    puts((char *)str);
}
