#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int pwd_command(char *args[])
{
  if (args[1] != NULL)
  {
    printf("\033[38;5;208m%s: Redirection Error: Too many arguments%s\n", "\033[1m", "\033[0m");
    return 1;
  }
  printf("\033[38;5;208m%s%s%s\n", "\033[1m", getcwd(NULL, 0), "\033[0m");
  return 0;
}