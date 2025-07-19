#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_FILE "devlog.txt"
#define MAX_ENTRY 1024

void add_entry(const char *entry) {
  FILE *f = fopen(LOG_FILE, "a");
  if (!f) {
    perror("Could not open log file");
    exit(EXIT_FAILURE);
  }
  // Get current time
  time_t now = time(NULL);
  struct tm *tm_info = localtime(&now);
  char timestr[32];
  strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", tm_info);

  fprintf(f, "[%s] %s\n", timestr, entry);
  fclose(f);
  printf("Added entry.\n");
}

void view_log() {
  FILE *f = fopen(LOG_FILE, "r");
  if (!f) {
    printf("No log file found.\n");
    return;
  }
  char line[MAX_ENTRY + 64];
  while (fgets(line, sizeof(line), f)) {
    printf("%s", line);
  }
  fclose(f);
}

void clear_log() {
  FILE *f = fopen(LOG_FILE, "w");
  if (!f) {
    perror("Could not clear log file");
    exit(EXIT_FAILURE);
  }
  fclose(f);
  printf("Log cleared.\n");
}

void usage(const char *prog) {
  printf("Usage:\n");
  printf("  %s add \"your log entry\"\n", prog);
  printf("  %s view\n", prog);
  printf("  %s clear\n", prog);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage(argv[0]);
    return 1;
  }
  if (strcmp(argv[1], "add") == 0) {
    if (argc < 3) {
      printf("Missing log entry.\n");
      usage(argv[0]);
      return 1;
    }
    add_entry(argv[2]);
  } else if (strcmp(argv[1], "view") == 0) {
    view_log();
  } else if (strcmp(argv[1], "clear") == 0) {
    clear_log();
  } else {
    usage(argv[0]);
    return 1;
  }
  return 0;
}
