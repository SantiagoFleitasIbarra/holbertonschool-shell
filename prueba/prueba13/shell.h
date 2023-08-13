#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

typedef struct PathNode
{
	char *directory;
	struct PathNode *next;
} PathNode;

void printenv_with_environ(void);
void compare_env_and_environ(char **env);
char *_getenv(const char *name);
void print_path_directories(void);
PathNode *build_path_list(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int main(int argc, char *argv[], char *env[]);

#endif
