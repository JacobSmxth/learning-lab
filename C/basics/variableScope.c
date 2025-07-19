#include <stdio.h>

// int result; // GLOBAL SCOPE (hard to debug)

int add(int x, int y) {
  int result = x + y;

  return result;
}

int subtract(int x, int y) {
  int result = x - y;

  return result;
}

int main() {

  int result = add(3, 4);
  printf("%d\n", add(5, 7));
  printf("%d", result);

  return 0;
}
