#include <math.h>
#include <stdio.h>
#include <string.h>

int main() {
  double first = 0.0;
  double second = 0.0;
  char type = '\0';
  double answer = 0.0;

  printf("CLI 2 Number Calculator\n");

  printf("Enter the first number: ");
  scanf("%lf", &first);

  printf("Enter the operator (+ - * /): ");
  scanf(" %c", &type);

  printf("Enter the second number: ");
  scanf("%lf", &second);

  switch (type) {
  case '+':
    answer = first + second;
    break;
  case '-':
    answer = first - second;
    break;
  case '*':
    answer = first * second;
    break;
  case '/':
    if (second == 0) {
      printf("Error: Can't divide by 0\n");
      return 1;
    }
    answer = first / second;
    break;
  default:
    printf("Please enter a valid operator\n");
    return 1;
  }

  printf("Result: %.3lf\n", answer);

  return 0;
}
