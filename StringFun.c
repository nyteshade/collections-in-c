#include <stdio.h>
#include "String.h"

int main() {
  NEString *s = NEStringCreate("Hello, World!");
  printf("%s\n", s->string);
  NEStringFree(s);

  return 0;
}