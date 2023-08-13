#include "shell.h"
/***/
void tokenizeInput(char *input, char **tokens, int *tokenCount)
{
	char *token = strtok(input, " \t\n");

	*tokenCount = 0;

	while (token != NULL)
	{
		tokens[(*tokenCount)++] = token;
		token = strtok(NULL, " \t\n");
	}
}
