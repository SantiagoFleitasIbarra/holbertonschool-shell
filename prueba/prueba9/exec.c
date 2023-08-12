# include "shell.h"
/***/
void execute_command(char **args)
{
	char *command = args[0];
	int status;
	int saved_stderr = dup(STDERR_FILENO);
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		char *full_path = get_absolute_path(command);

		if (full_path == NULL)
			full_path = search_path(command);
		if (full_path != NULL)
		{
			dup2(STDOUT_FILENO, STDERR_FILENO);
			
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

		dup2(saved_stderr, STDERR_FILENO);
		close(saved_stderr);
	}
}
