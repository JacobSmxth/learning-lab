#include <math.h>
#include <stdio.h>
#include <string.h>

void toPounds(double kilos) {
  double pounds = kilos * 2.204623;
  printf("%.2lf kilograms is equal to %.2lf pounds\n", kilos, pounds);
}

void toKilos(double pounds) {
  double kilos = pounds * 0.45349237;
  printf("%.2lf pounds is equal to %.2lf kilograms\n", pounds, kilos);
}

int main() {
  int choice = 0;
  double weight = 0.0;

  printf("Weight Conversion Calculator\n");

  printf("1. Kilograms to Pounds\n2. Pounds to Kilograms\n");

  printf("Enter your choice (1 or 2): ");
  scanf("%d", &choice);

  if (choice == 1) {
    printf("Enter the weight in kilograms: ");
    scanf("%lf", &weight);
    toPounds(weight);

  } else if (choice == 2) {
    printf("Enter the weight in pounds: ");
    scanf("%lf", &weight);
    toKilos(weight);
  } else {
    printf("Please enter either 1 or 2");
  }

  return 0;
}
