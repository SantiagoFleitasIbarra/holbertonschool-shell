# ifndef _SHELL_H_
# define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#define MAX_INPUT_SIZE 1024
extern char **environ;
void display_prompt(void);
void execute_command(char **args);
int is_absolute_path(char *command);
void handle_noninteractive_mode(void);
void tokenize_input(char *input, char **args);
void execute_input(char **args);
void search_and_execute(char **args);
int main(void);
void handle_cd(char **args);
void handle_help(void);
void handle_setenv(char **args);
void handle_unsetenv(char **args);
# endif
