#include <stdio.h>

float thing(char type, float num) {
  float final = 0.0;

  if (type == '.') {
    final = num / 100;
  } else {
    final = num * 100;
  }

  return final;
}

int main() {

  printf("%.2f\n", thing('%', 50));
  return 0;
}
