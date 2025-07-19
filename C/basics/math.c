#include <math.h>
#include <stdio.h>

int main() {

  double radius = 0.0f;
  double area = 0.0f;
  double sArea = 0.0f;
  double volume = 0.0f;

  const float PI = 3.14159;

  printf("Enter the radius: ");
  scanf("%lf", &radius);

  area = (PI * (pow(radius, 2)));
  printf("Area: %2.lf\n", area);

  sArea = 4 * (PI * (pow(radius, 2)));
  printf("Surface Area: %.2lf\n", sArea);

  volume = (4.0 / 3.0) * (PI * (pow(radius, 3)));
  printf("Volume: %.2lf\n", volume);

  return 0;
}
