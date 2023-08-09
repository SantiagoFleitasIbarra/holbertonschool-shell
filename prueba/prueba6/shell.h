# ifndef _SHELL_H_
# define _SHELL_H_
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
#define MAX_INPUT_LENGTH 1024
void display_prompt(void);
void tokenize_input(char *input, char **args);
void execute_command(char **args);
void interactive_mode(void);
void non_interactive_mode(const char *filename);
int main(int argc, char *argv[]);
# endif
