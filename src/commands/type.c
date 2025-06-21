#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// Function to check if a file exists and is executable
int is_executable(const char *path)
{
  struct stat st;
  if (stat(path, &st) == 0)
  {
    return S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR);
  }
  return 0;
}

// Function to search for a command in PATH
char *find_command_in_path(const char *command)
{
  char *path_env = getenv("PATH");
  if (!path_env)
  {
    return NULL;
  }

  // Make a copy of PATH to avoid modifying the original
  char *path_copy = strdup(path_env);
  if (!path_copy)
  {
    return NULL;
  }

  char *dir = strtok(path_copy, ":");
  while (dir != NULL)
  {
    // Allocate space for full path: dir + "/" + command + null terminator
    char *full_path = malloc(strlen(dir) + strlen(command) + 2);
    if (!full_path)
    {
      free(path_copy);
      return NULL;
    }

    sprintf(full_path, "%s/%s", dir, command);

    if (is_executable(full_path))
    {
      free(path_copy);
      return full_path;
    }

    free(full_path);
    dir = strtok(NULL, ":");
  }

  free(path_copy);
  return NULL;
}

int type_command(char *args[])
{
  char *command = args[1];
  if (command == NULL)
  {
    return 1;
  }
  if (strcmp(command, "echo") == 0 || strcmp(command, "exit") == 0 ||
      strcmp(command, "type") == 0 || strcmp(command, "pwd") == 0 ||
      strcmp(command, "cd") == 0 || strcmp(command, "clear") == 0)
  {
    printf("%s is a shell builtin\n", command);
  }
  else
  {
    char *full_path = find_command_in_path(command);
    if (full_path)
    {
      printf("%s is %s\n", command, full_path);
      free(full_path);
    }
    else
    {
      printf("%s: not found\n", command);
    }
  }
  return 1;
}