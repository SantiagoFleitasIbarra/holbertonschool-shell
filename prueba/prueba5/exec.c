# include "shell.h"
/***/
void execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		char *args[2];
		args[0] = command;
		args[1] = NULL;

		if (execve(command, args, environ) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
