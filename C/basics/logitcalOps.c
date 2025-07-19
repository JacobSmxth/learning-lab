#include <stdio.h>

int main() {

  int temp = 64;

  if (temp > 42 && temp <= 74) {
    printf("The temp is GOOD\n");
  } else if (temp <= -100 || temp >= 140) {
    printf("The temp will kill you!\n");
  } else {
    printf("The temp is BAD\n");
  }

  return 0;
}
