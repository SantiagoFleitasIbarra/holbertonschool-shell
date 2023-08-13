#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void tokenizeInput(char *input, char **tokens, int *tokenCount);
int executeCommand(char **tokens, int tokenCount);
int main(int argc, char *argv[]);

#endif
