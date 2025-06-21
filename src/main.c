#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>
#include "builtins.h"
#include "utils/banner.h"
#include "utils/donut.h"
#include "utils/parse_command.h"

int main(int argc, char **argv) {
  // Show startup animation and banner
  print_startup_animation();
  donut_startup_animation(10); // Show donut for 10 frames
  print_colored_banner();

  while (1) {
    // Colorful prompt
    char *prompt = "\033[38;5;51m\033[1moh-my-shell\033[0m\033[38;5;46m\033[1m>\033[0m ";
    char *input = readline(prompt);
    
    if (input == NULL) {
      printf("\033[38;5;208m%sGoodbye! 👋%s\n", "\033[1m", "\033[0m");
      break;
    }

    // Skip empty input
    if (strlen(input) == 0) {
      free(input);
      continue;
    }

    char *args[100];
    int max_args = 100;
    int parse_result = parse_command(input, args, max_args);
    
    if (parse_result == -1) {
      printf("\033[38;5;208m%sError: Unterminated quote%s\n", "\033[1m", "\033[0m");
      free(input);
      continue;
    }

    if (builtins_init(args) == 1) {
      printf("\033[38;5;208m%sUnknown command: %s%s\n", "\033[1m", input, "\033[0m");
    }

    // Clean up allocated memory for args
    for (int j = 0; j < parse_result; j++) {
      free(args[j]);
    }

    free(input);
  }
  
  return 0;
}