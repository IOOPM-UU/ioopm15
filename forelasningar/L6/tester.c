#include <string.h>
#include <stdio.h>

#include "asker.h"

int main(int argc, char *argv[]){
  char *s = askString("Testing");
  if(strcmp(s, "Correct!") == 0){
    printf("Test passed!\n");
  }else{
    printf("Test failed!\n");
  }
  return 0;
}