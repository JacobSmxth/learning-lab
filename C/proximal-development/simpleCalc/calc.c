#include <stdbool.h>
#include <stdio.h>

int askType();
void checkType(int choice);
void clearBuffer();
void add();
void subtract();
void multiply();
void divide();
void sqr();

int main() {
  printf("====== Calculator ======\n");
  printf("\n");
  checkType(askType());
  return 0;
}

void checkType(int choice) {
  switch (choice) {
  case 1:
    add();
    break;
  case 2:
    // subtract();
    break;
  case 3:
    // multiply();
    break;
  case 4:
    // divide();
    break;
  case 5:
    // sqr();
    break;
  case 6:
    break;
  default:
    perror("How did this happen?");
    break;
  }
}

int askType() {

  printf("What calculation will you be making?\n");
  printf(" 1. Addition\n");
  printf(" 2. Subtraction\n");
  printf(" 3. Multiplication\n");
  printf(" 4. Division\n");
  printf(" 5. Square\n");
  printf(" 6. Square Root\n");
  printf("Make your choice: ");

  bool validInput = false;
  int choice = 0;
  while (!validInput) {
    if (scanf("%d", &choice) != 1) {
      clearBuffer();
      break;
    }
    if (choice > 6 || choice < 1) {
      continue;
    } else {
      validInput = true;
    }
  }

  return choice;
}

void add() {
  float x = 0.0f;
  float y = 0.0f;
  float total = 0.0f;

  bool validInput = false;
  printf("What is first value: ");
  while (!validInput) {
    if (scanf("%f", &x) != 1) {
      clearBuffer();
      continue;
    } else {
      total += x;
      validInput = true;
    }
  }

  validInput = false;
  printf("What is second value: ");
  while (!validInput) {
    if (scanf("%f", &y) != 1) {
      clearBuffer();
      continue;
    } else {
      total += y;
      validInput = true;
    }
  }

  printf("=====================\n");
  printf("++++ Calculation ++++\n");
  printf("=====================\n");
  printf("%.2f + %.2f is %.2f\n", x, y, total);
}

void clearBuffer() {
  int c;
  while (getchar() != '\n' && c != EOF)
    ;
}
