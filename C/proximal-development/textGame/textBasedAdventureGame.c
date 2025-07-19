#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define WORLD_ROOM_COUNT 3
#define WORLD_ITEM_COUNT 4

typedef enum { SW = 1, FP, HW } POTION_TYPE;
typedef enum { FL = 4, PS, CS } WEAPON_TYPE;
typedef enum { BC = 7, TH, KA } ARMOR_TYPE;

typedef enum {
  STATE_EXITING = 1000,
  STATE_MAIN_MENU,
  STATE_INITIALIZING,
  STATE_PLAYING,
} GameState;

typedef struct {
  char name[20];
  char description[50];
  int id;
} Item;

typedef struct Room {
  char name[20];
  char description[150];
  char hint[100];
  Item **items;
  int item_count;
  int item_cap;
  struct Room *north;
  struct Room *south;
  struct Room *east;
  struct Room *west;
} Room;

typedef struct {
  char name[20];
  char description[50];
  Item **items;
  int item_count;
  int item_cap;
  Room *starting_room;
} NPC;

// Global arrays
Room *g_rooms[WORLD_ROOM_COUNT];
Item *g_items[WORLD_ITEM_COUNT];

typedef struct {
  char name[20];
  Room *current_location;
  Room *previous_location;
  Item *inventory[10];
  int inv_count;
} Player;

// == FUNCTION PROTOTYPES == \\

int get_terminal_width();
void centerText(int tWidth, const char *format, ...);
void seperator_line(int tWidth);
void clear_screen();
int display_main_menu(int tWidth, Player *player);
void initialize_game(int tWidth, Player *player);
void game_loop(int tWidth, Player *player);

void takeItem(Player *player, const char *itemName);
void dropItem(Player *player, const char *itemName);
void moveLocation(Player *player, const char *direction);

void cleanup_game();

// == MAIN FUNCTION == \\

int main() {
  clear_screen();
  Player player;
  GameState current_state = STATE_MAIN_MENU;

  int tWidth = get_terminal_width();
  printf("Enter your name: ");
  fgets(player.name, sizeof(player.name), stdin);
  player.name[strlen(player.name) - 1] = '\0';

  while (current_state != STATE_EXITING) {
    switch (current_state) {
    case STATE_MAIN_MENU:
      clear_screen();
      if (display_main_menu(tWidth, &player) == 1) {
        current_state = STATE_INITIALIZING;
      } else {
        current_state = STATE_EXITING;
      }
      break;
    case STATE_INITIALIZING:
      clear_screen();
      initialize_game(tWidth, &player);
      current_state = STATE_PLAYING;
      break;
    case STATE_PLAYING:
      clear_screen();
      game_loop(tWidth, &player);
      current_state = STATE_EXITING;
      break;
    case STATE_EXITING:
      break;
    default:
      current_state = STATE_EXITING;
      break;
    }
  }

  cleanup_game();
  return 0;
}

// == MAIN MENU DISPLAY FUNCTION == \\

int display_main_menu(int tWidth, Player *player) {
  int choice = 0;
  seperator_line(tWidth);
  printf("\n\n");

  centerText(tWidth, "THE ECHO OF A NAME");
  printf("\n\n");
  centerText(tWidth, "1) Play Game");
  printf("\n");
  centerText(tWidth, "2) Exit Game");
  printf("\n");

  printf("\n\n");
  seperator_line(tWidth);
  bool validInput = false;

  do { // Go until valid input
    printf(" > ");
    if (scanf("%d", &choice) != 1) {
      while (getchar() != '\n')
        ;
      continue;
    }
    while (getchar() != '\n')
      ;
    if (choice > 2 || choice < 1) {
      continue;
    }
    validInput = true;
  } while (!validInput);

  return choice;
}

// == INITIALIZE GAME FUNCTION == \\

void initialize_game(int tWidth, Player *player) {
  // Create all items
  g_items[0] = malloc(sizeof(Item));
  strcpy(g_items[0]->name, "Flashlight");
  strcpy(g_items[0]->description, "It's simply a flashlight.");
  g_items[0]->id = FL;

  g_items[1] = malloc(sizeof(Item));
  strcpy(g_items[1]->name, "Salty Mixture");
  strcpy(g_items[1]->description, "Ew. Gross.");
  g_items[1]->id = SW;

  g_items[2] = malloc(sizeof(Item));
  strcpy(g_items[2]->name, "Baseball Cap");
  strcpy(g_items[2]->description, "Go Braves!");
  g_items[2]->id = BC;

  g_rooms[0] = malloc(sizeof(Room));
  g_rooms[1] = malloc(sizeof(Room));
  g_rooms[2] = malloc(sizeof(Room));

  Room *dungeon = g_rooms[0];
  strcpy(dungeon->name, "A Holding Cell");
  strcpy(dungeon->description, "Cold cinderblock walls and rusted iron bars "
                               "cage you in. This is a prison cell. The exit "
                               "is straight north. unlocked...");
  strcpy(dungeon->hint,
         "Something clattered to the ground. Maybe a light source?");

  dungeon->item_cap = 5;
  dungeon->items = malloc(dungeon->item_cap * sizeof(Item *));

  dungeon->items[0] = g_items[0];
  dungeon->items[1] = g_items[1];
  dungeon->item_count = 2;

  Room *hallway = g_rooms[1];
  strcpy(hallway->name, "Gloomy Hallway");
  strcpy(hallway->description,
         "it stretches far down. There is a window to the left and it's just "
         "as dark outside. What do I do.");
  strcpy(hallway->hint, "It's a hallway. Follow it.");
  hallway->item_count = 0;
  hallway->item_cap = 5;
  hallway->items = NULL;

  Room *library = g_rooms[2];
  strcpy(library->name, "The Library");
  strcpy(
      library->description,
      "Overturned shelves and scattered papers fill this wrecked room. A "
      "single flickering lamp illuminates it. A scurrying sound in the back.");
  strcpy(library->hint, "There must be something in here to help me");

  library->item_cap = 5;
  library->items = malloc(library->item_cap * sizeof(Item *));

  library->items[0] = g_items[2];
  library->item_count = 1;

  // Linking rooms together

  dungeon->north = hallway;
  dungeon->south = NULL;
  dungeon->east = NULL;
  dungeon->west = NULL;

  hallway->south = dungeon;
  hallway->east = NULL;
  hallway->west = NULL;
  hallway->north = library;

  library->north = NULL;
  library->east = NULL;
  library->west = NULL;
  library->south = hallway;

  player->current_location = dungeon;
  player->previous_location = NULL;
  player->inv_count = 0;
}

void game_loop(int tWidth, Player *player) {
  int checkFirst = 0;
  char command[100];
  bool isRunning = true;
  bool hasLight;

  while (isRunning) {
    if (checkFirst == 0) {
      seperator_line(tWidth);
      centerText(
          tWidth,
          "Cold. That's the first thing you feel, seeping into you from a "
          "hard floor. The second is a foul, coppery taste... blood.\n");
      centerText(
          tWidth,
          "You try to grasp a thought, any thought, but find only a hollow "
          "ache where your memories should be. All is quiet, except for one "
          "word that pulses behind your eyes.\n");
      centerText(
          tWidth,
          "%s. The name feels foreign, yet it's the only thing you have. "
          "%s... %s... Who is %s?\n\n",
          player->name, player->name, player->name, player->name);
      centerText(tWidth,
                 "Something clatters to the ground as if it's been dropped.\n");
    }
    checkFirst = 1;
    hasLight = false;
    seperator_line(tWidth);
    printf("\n");

    for (int i = 0; i < player->inv_count; i++) {
      if (player->inventory[i]->id == FL) {
        hasLight = true;
        break;
      }
    }

    if (hasLight) {
      centerText(tWidth, "You are in %s\n", player->current_location->name);
      centerText(tWidth, "%s\n", player->current_location->description);
      centerText(tWidth, "Items in room\n");
      centerText(tWidth, "=============\n");
      if (player->current_location->item_count == 0) {
        centerText(tWidth, "- Nothing\n");
      } else {
        for (int i = 0; i < player->current_location->item_count; i++) {
          centerText(tWidth, "- %s\n\n",
                     player->current_location->items[i]->name);
        }
      }
    } else {
      centerText(tWidth, "You are in darkness\n");
      centerText(tWidth, "There must be some sort of light source nearby\n");
      centerText(tWidth, "You can't see anything. It's too dark\n\n");
    }

    seperator_line(tWidth);
    printf(" > ");
    fgets(command, sizeof(command), stdin);
    command[strlen(command) - 1] = '\0';
    char *action = strtok(command, " \n");
    char *thing = strtok(NULL, "\n");

    if (action == NULL) {
      continue;
    }
    if (strcasecmp(action, "quit") == 0) { // Command to quit the game
      isRunning = false;
    } else if (strcasecmp(action, "inventory") == 0) {
      printf("You are carrying: ");
      if (player->inv_count == 0) {
        printf("- Nothing\n");
      }
      for (int i = 0; i < player->inv_count; i++) {
        printf("- %s\n", player->inventory[i]->name);
      }
    } else if (strcasecmp(action, "take") == 0) {
      if (thing != NULL) {
        takeItem(player, thing);
      } else {
        printf("What do you want to take?\n");
      }
    } else if (strcasecmp(action, "drop") == 0) {
      if (thing != NULL) {
        dropItem(player, thing);
      } else {
        printf("What do you want to drop?\n");
      }
    } else if (strcasecmp(action, "go") == 0) {
      if (thing != NULL) {
        moveLocation(player, thing);
      } else {
        printf("Where do you want to go??\n");
      }
    } else if (strcasecmp(action, "hint") == 0) {
      printf("%s\n", player->current_location->hint);
    } else {

      printf("\n\nI don't understand that command\n\n\n");
      printf("Use the following: quit, inventory, take ..., drop ..., go "
             "...\n\n\n");
    }
  }
}

void cleanup_game() {
  for (int i = 0; i < WORLD_ROOM_COUNT; i++) {
    if (g_rooms[i] != NULL) {
      free(g_rooms[i]->items);
    }
  }

  for (int i = 0; i < WORLD_ROOM_COUNT; i++) {
    free(g_rooms[i]);
  }

  for (int i = 0; i < WORLD_ITEM_COUNT; i++) {
    free(g_items[i]);
  }
}

// Calculate the terminals width to make top border
int get_terminal_width() {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
    perror("ioctl");
    return -1;
  }

  return ws.ws_col;
}

void takeItem(Player *player, const char *itemName) {
  Room *current_room = player->current_location;

  // Find the item in room

  int item_index_in_room = -1;
  Item *item_to_take = NULL;

  for (int i = 0; i < current_room->item_count; i++) {
    if (strcasecmp(current_room->items[i]->name, itemName) == 0) {
      item_index_in_room = i;
      item_to_take = current_room->items[i];
      break; // No need to keep looking
    }
  }
  if (item_to_take == NULL) {
    printf("There is no '%s' to take\n", itemName);
    return;
  }

  if (player->inv_count >= 10) {
    printf("Your inventory is full.\n");
    return;
  }

  player->inventory[player->inv_count] = item_to_take;
  player->inv_count++;

  current_room->item_count--;
  current_room->items[item_index_in_room] =
      current_room->items[current_room->item_count];
  current_room->items[current_room->item_count] = NULL;

  printf("You took the %s.\n", item_to_take->name);
}

void dropItem(Player *player, const char *itemName) {
  Room *current_room = player->current_location;

  int item_index_in_inv = -1;
  Item *item_to_take = NULL;

  for (int i = 0; i < player->inv_count; i++) {
    if (strcasecmp(player->inventory[i]->name, itemName) == 0) {
      item_index_in_inv = i;
      item_to_take = player->inventory[i];
      break; // No need to continue to look
    }
  }

  if (item_to_take == NULL) {
    printf("There is no '%s' to drop\n", itemName);
    return;
  }

  if (current_room->items == NULL) {
    current_room->items = malloc(current_room->item_cap * sizeof(Item *));
    if (current_room->items == NULL) {
      printf("Error: Couldn't allocation memory for room inventory. (GAME BUG) "
             "\n");
      return;
    }
  }

  if (current_room->item_count >= current_room->item_cap) {
    printf("You can't drop that here the room is full.\n");
    return;
  }

  current_room->items[current_room->item_count] = item_to_take;
  current_room->item_count++;

  player->inv_count--;
  player->inventory[item_index_in_inv] = player->inventory[player->inv_count];
  player->inventory[player->inv_count] = NULL;

  printf("You dropped the %s.\n", item_to_take->name);
}

// == MOVE LOCATION FUNCTION == \\

void moveLocation(Player *player, const char *direction) {
  clear_screen();
  Room *target_room = NULL;

  if (strcasecmp(direction, "north") == 0) {
    target_room = player->current_location->north;
  } else if (strcasecmp(direction, "south") == 0) {
    target_room = player->current_location->south;
  } else if (strcasecmp(direction, "east") == 0) {
    target_room = player->current_location->east;
  } else if (strcasecmp(direction, "west") == 0) {
    target_room = player->current_location->west;
  } else if (strcasecmp(direction, "back") == 0) {
    target_room = player->previous_location;
  } else {
    printf("That direction doesn't exist!");
    return;
  }

  if (target_room == NULL) {
    printf("You can't go %s!\n", direction);
    return;
  } else {
    printf("You go %s...\n", direction);
    player->previous_location = player->current_location;
    player->current_location = target_room;
  }
}

// Use the terminals width to make a function to center text for clean look
void centerText(int tWidth, const char *format, ...) {
  char *buffer;

  va_list args;

  va_start(args, format);

  va_list args_copy;
  va_copy(args_copy, args);

  int len = vsnprintf(NULL, 0, format, args_copy);
  va_end(args_copy);

  buffer = (char *)malloc(len + 1);
  if (buffer == NULL) {
    va_end(args);
    return;
  }

  vsnprintf(buffer, len + 1, format, args);

  va_end(args);

  for (int i = 0; i < (tWidth - len) / 2; i++) {
    printf(" ");
  }
  printf("%s", buffer);

  free(buffer);
}

// Use the terminals width to make a seperator line
void seperator_line(int tWidth) {
  for (int i = 0; i < tWidth; i++) {
    printf("=");
  }
}

void clear_screen() {
#ifdef _WIN32
  // For Windows
  system("cls");
#else
  // For Linux, macOS, and others
  system("clear");
#endif
}
