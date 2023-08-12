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
		char *full_path = get_full_path(command);

		if (full_path != NULL)
		{
			if (access(full_path, X_OK) == 0)
			{
				if (execv(args[0], args) == -1)
					perror(args[0]);
			}
			else
				fprintf(stderr, "mi_shell: %s: Permission denied\n", full_path);
			free(full_path);
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
		perror("fork");
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

