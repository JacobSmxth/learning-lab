#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  // int age = 0;
  // int ageDiff = 0;
  // int timeUntilDrink = 0;

  // printf("Enter your age: ");
  // if (scanf("%d", &age) != 1) {
  //   printf("Invalid input. Please enter a number.\n");
  //   return 1;
  // }

  // ageDiff = age - 21;

  // if (age >= 18) {
  //   printf("You're an adult\n");
  // } else {
  //   printf("You are underage\n");
  // }

  // if (ageDiff < 0) {
  //   timeUntilDrink = abs(ageDiff);
  //   printf("You have %d year/s until you can drink.\n", timeUntilDrink);
  // } else if (ageDiff >= 0) {
  //   printf("Go get yourself a beer!\n");
  // }

  char name[50] = "";

  printf("Enter your name: ");
  fgets(name, sizeof(name), stdin);
  name[strlen(name) - 1] = '\0';

  if (strlen(name) == 0) {
    printf("You didn't enter a name.\n");
  } else {
    printf("Hi there, %s\n", name);
  }

  return 0;
}
