#include "shell.h"
/***/
int executeCommand(char **tokens, int tokenCount)
{
	pid_t pid = fork();

	(void)tokenCount;

	if (pid == 0)
	{
		if (execvp(tokens[0], tokens) == -1)
		{
			perror("simple_shell");
			exit(EXIT_FAILURE);
		}
	} else if (pid > 0)
		wait(NULL);
	else
	{
		perror("simple_shell");
		return (-1);
	}
	return (0);
}
