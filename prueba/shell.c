#include "shell.h"
/***/
int main(int ac, char **argv)
{
	char *prompt = "$ ", *lineptr = NULL, *lineptr_copy = NULL, *token;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0, i;

	(void)ac;
	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1)
		{
			printf("\n");
			break;
			return (-1);
		}
		if (strcmp(lineptr, "exit\n") == 0)
		{
			free(lineptr);
			break;
		}
		lineptr_copy = malloc(sizeof(char) * nchars_read);
		if (lineptr_copy == NULL)
			return (-1);
		strcpy(lineptr_copy, lineptr);
		token = strtok(lineptr, delim);
		while (token != NULL)
			num_tokens++, token = strtok(NULL, delim);
		argv = malloc(sizeof(char *) * num_tokens);
		num_tokens++, token = strtok(lineptr_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token), token = strtok(NULL, delim);
		}
	argv[i] = NULL, execmd(argv);
	free(lineptr_copy), free(lineptr);
	}
	return (0);
}
