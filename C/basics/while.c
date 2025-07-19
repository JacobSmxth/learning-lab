#include <stdio.h>

int main() {

  int age = 0;
  int i = 0;
  while (i == 0) {
    printf("Enter your age: ");
    if (scanf("%d", &age) != 1) {
      printf("Thats not your age\n");
      age = 0;
      continue;
    } else {
      i = 1;
    }
  }
  printf("You are %d years old!\n", age);

  return 0;
}
