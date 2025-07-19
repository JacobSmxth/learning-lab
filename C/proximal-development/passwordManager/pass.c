#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char username[40];
  char password[40];
} Account;

typedef struct Node {
  Account *account;
  struct Node *next;
} Node;

void viewPasswords();
void addPassword(Node **head);
void delPassword();
void nukePasswords();

int main() {
  Node *head = NULL;
  addPassword(&head);

  free(head);
  return 0;
}

void addPassword(Node **head) {
  if (head == NULL) {
    head = malloc(sizeof(Node));
    (*head)->account = malloc(sizeof(Account));
  }
  Node *current = *head;

  while (current->next != NULL) {
    current = current->next;
  }

  char buffer[40];
  char choice[5];
  printf("Time to add a password!\n");

  fgets(buffer, sizeof(buffer), stdin);
  buffer[strlen(buffer) - 1] = '\0';
  bool validInput = false;
  do {
    printf("I got '%s'. Is that right? (y/n): ", buffer);
    fgets(choice, sizeof(choice), stdin);
    choice[strlen(choice) - 1] = '\0';
    if (strlen(choice) > 1) {
      while (getchar() != '\n')
        ;
      continue;
    } else {
      if (choice[0] == 'y' || choice[0] == 'n') {
        validInput = true;
      }
    }
  } while (!validInput);

  if (choice[0] != 'y') {
    return;
  }

  printf("Username: %s\n", buffer);

  snprintf(current->account->username, sizeof(current->account->username), "%s",
           buffer);
}
