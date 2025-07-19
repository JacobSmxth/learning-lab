#include <stdbool.h>
#include <stdio.h>

void hello(char name[], int age); // function prototype
bool ageCheck(int age);

int main() {

  hello("Spongebob", 30);

  if (ageCheck(18)) {
    printf("You are old enough\n");
  } else {
    printf("U too yung cuzzo\n");
  }
  return 0;
}

void hello(char name[], int age) {
  printf("Hello %s\n", name);
  printf("You are %d years old\n", age);
}

bool ageCheck(int age) { return age >= 16; }
