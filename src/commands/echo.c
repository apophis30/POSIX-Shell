#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int echo_command(char *args[])
{
  if (args[1] != NULL)
  {
    int suppress_newline = 0;
    int start_arg = 1;

    if (args[1] != NULL && strcmp(args[1], "-n") == 0)
    {
      suppress_newline = 1;
      start_arg = 2;
    }

    for (int i = start_arg; args[i] != NULL; i++)
    {
      if (i > start_arg)
        printf(" ");
      printf("%s", args[i]);
    }

    if (!suppress_newline)
    {
      printf("\n");
    }
    return 1;
  }
  return 0;
}