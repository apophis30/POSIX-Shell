#include "builtins.h"
#include "commands/builtin_header.h"

int builtins_init(char *args[]) {
  if (strcmp(args[0], "exit") == 0) {
    exit_command(args);
  } else if (strcmp(args[0], "cd") == 0) {
    cd_command(args);
  } else if (strcmp(args[0], "pwd") == 0) {
    pwd_command(args);
  } else if (strcmp(args[0], "type") == 0) {
    type_command(args);
  } else if (strcmp(args[0], "echo") == 0) {
    echo_command(args);
  } else if (strcmp(args[0], "clear") == 0) {
    clear_command(args);
  } else {
    return 1;
  }
  return 0;
}