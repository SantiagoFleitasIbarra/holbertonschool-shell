# ifndef _SHELL_H_
# define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 1024
extern char **environ;
void print_prompt(void);
void execute_command(char *command);
int main(void);
# endif
