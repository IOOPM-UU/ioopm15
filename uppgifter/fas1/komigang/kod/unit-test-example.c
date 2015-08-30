#include "minute.h"
#include<string.h>

void testStrlen() {
  assertTrue(strlen("Hej")		    == 3);
  assertTrue(strlen("")			    == 0);
  assertTrue(strlen("Hokus pokus filiokus") == 20);
}

int main(void) {
  testStrlen();
  report();
  return 0;
}
