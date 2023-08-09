# include "shell.h"
/***/
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr, "bash: %s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0)
		perror("shell");
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
