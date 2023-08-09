#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "error_handler.h"

#define MAX_INPUT_SIZE 1024

void display_prompt(void);
int is_absolute_path(char *command);
void handle_noninteractive_mode(void);
void tokenize_input(char *input, char **args);
void execute_command(char **args);
void execute_input(char **args);
void search_and_execute(char **args);
void print_environment(void);
void execute_external_command(char **args);
#endif
