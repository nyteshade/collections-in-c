#include <stdio.h>

int main(int argc, char **argv) {
  long a = 256;

  printf("%d\n", *((char *)&a));
  printf("%d\n", *((char *)&a + 1));
  printf("%d\n", *((char *)&a + 2));
  printf("%d\n", *((char *)&a + 3));

  return 0;
}
