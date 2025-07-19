#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *name;
  bool completed;
  int priority;
} Task;

typedef struct Node {
  Task *task;
  struct Node *next;
} Node;

Task *createTask(const char *name, bool completed, int priority) {
  Task *t = malloc(sizeof(*t));
  if (!t) {
    printf("malloc error in task creation");
    exit(1);
  }

  size_t len = strlen(name) + 1;
  t->name = malloc(len);
  if (!t->name) {
    printf("malloc error in name");
    exit(1);
  }
  memcpy(t->name, name, len);

  t->completed = completed;
  t->priority = priority;
  return t;
}

Node *createNode(Task *task) {
  Node *n = malloc(sizeof(*n));
  if (!n) {
    printf("malloc error in Node creation");
    exit(1);
  }
  n->task = task;
  n->next = NULL;
  return n;
}

void appendTask(Node **head, Task *task) {
  Node *n = createNode(task);
  if (*head == NULL) {
    *head = n;
  } else {
    Node *current = *head;
    while (current->next) {
      current = current->next;
    }
    current->next = n;
  }
}

void freeList(Node *head) {
  while (head) {
    Node *tmp = head->next;
    free(head->task->name);
    free(head->task);
    free(head);
    head = tmp;
  }
}

int main(void) {
  Node *head = NULL;

  appendTask(&head, createTask("Walk Dog", false, 5));
  printf("First Task: %s (priority %d)\n", head->task->name,
         head->task->priority);

  freeList(head);
  return 0;
}
