#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exit_command(char *args[])
{
  if (args[1] != NULL)
  {
    if (args[1][0] == '0')
    {
      printf("\033[38;5;208m%sGoodbye! 👋%s\n", "\033[1m", "\033[0m");
      return 0;
      exit(0);
    }
    else
    {
      printf("\033[38;5;208m%sError: Invalid exit code%s\n", "\033[1m", "\033[0m");
      return 1;
      exit(1);
    }
  }
  printf("\033[38;5;208m%sGoodbye! 👋%s\n", "\033[1m", "\033[0m");
  exit(0);
}