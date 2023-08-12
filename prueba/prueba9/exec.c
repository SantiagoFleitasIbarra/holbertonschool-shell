# include "shell.h"
/***/
void execute_command(char **args)
{
	char *command = args[0];
	int status;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		char *full_path = get_absolute_path(command);

		if (full_path == NULL)
			full_path = search_path(command);
		if (full_path != NULL)
		{
			execv(full_path, args);
			perror(command);
			free(full_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			fprintf(stderr, "%s: Command not found\n", command);
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0)
		perror("fork");
	else
	{
		waitpid(pid, &status, 0);
	}
}
