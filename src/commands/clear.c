#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clear_command(char *args[])
{
  printf("\033[2J\033[H");
  return 0;
}