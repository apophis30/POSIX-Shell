#include "builtins.h"

void builtins_init(char *input) {
  if (strcmp(input, "exit") == 0) {
    printf("\033[38;5;208m%sGoodbye! 👋%s\n", "\033[1m", "\033[0m");
    exit(0);
  } else {
    printf("\033[38;5;208m%sUnknown command: %s%s\n", "\033[1m", input, "\033[0m");
  }
}