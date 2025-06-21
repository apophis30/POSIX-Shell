#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

char *expand_tilde(const char *path)
{
  if (path[0] == '~')
  {
    char *home = getenv("HOME");
    if (!home)
    {
      return NULL;
    }

    // Allocate space for home + rest of path + null terminator
    char *expanded = malloc(strlen(home) + strlen(path));
    if (!expanded)
    {
      return NULL;
    }

    if (path[1] == '\0')
    {
      // Just "~" - return home directory
      strcpy(expanded, home);
    }
    else if (path[1] == '/')
    {
      // "~/something" - home directory + rest of path
      sprintf(expanded, "%s%s", home, path + 1);
    }
    else
    {
      // "~something" - not supported in this stage, return NULL
      free(expanded);
      return NULL;
    }

    return expanded;
  }

  // No tilde, return a copy of the original path
  return strdup(path);
}

int cd_command(char *args[])
{
  if (args[1] == NULL)  
  {
    printf("\033[38;5;208m%s: Redirection Error: No argument provided%s\n", "\033[1m", "\033[0m");
    char *home = getenv("HOME");
    if (!home)
    {
      return 1;
    }
    if (chdir(home) != 0)
    {
      printf("\033[38;5;208m%s: Redirection Error: %s%s\n", "\033[1m", strerror(errno), "\033[0m");
      return 1;
    }
    return 0;
  }

  char *expanded_path = expand_tilde(args[1]);
  if (!expanded_path)
  {
    printf("\033[38;5;208m%s: Redirection Error: Failed to expand tilde%s\n", "\033[1m", "\033[0m");
    return 1;
  }

  if (chdir(expanded_path) != 0)
  {
    printf("\033[38;5;208m%s: Redirection Error: %s%s\n", "\033[1m", strerror(errno), "\033[0m");
  }

  free(expanded_path);
  return 0;
}