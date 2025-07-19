#include <math.h>
#include <stdio.h>

int main() {
  double principal = 0.0;
  double rate = 0.0;
  int years = 0;
  int timesCompounded = 0;
  double total = 0.0;

  printf("Enter the principal (P): ");
  scanf("%lf", &principal);

  printf("Enter the interest rate %% (r): ");
  scanf("%lf", &rate);
  rate /= 100; // Change user input to decimal

  printf("Enter the # of years (t): ");
  scanf("%d", &years);

  printf("Enter the # of times compounded per year (n): ");
  scanf("%d", &timesCompounded);

  total = principal * pow(1 + (rate / timesCompounded), years);

  printf("After %d years, the total will be $%.2f\n", years, total);
}
