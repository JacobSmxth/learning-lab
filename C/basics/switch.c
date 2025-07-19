#include <stdio.h>

int main() {

  char dayOfWeek = '\0';

  printf("Please enter a day of the week (M,T,W,R,F,S,U): ");
  scanf("%c", &dayOfWeek);

  switch (dayOfWeek) {
  case 'M':
    printf("It is Monday\n");
    break;
  case 'T':
    printf("It is Tuesday\n");
    break;
  case 'W':
    printf("It is Wednesday\n");
    break;
  case 'R':
    printf("It is Thursday\n");
    break;
  case 'F':
    printf("It is Friday\n");
    break;
  case 'S':
    printf("It is Saturday\n");
    break;
  case 'U':
    printf("It is Sunday\n");
    break;
  default:
    printf("Please only enter one of the letters");
    break;
  }

  return 0;
}
