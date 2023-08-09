# include "shell.h"
# include "error_handler.h"
/***/
void execute_external_command(char **args)
{
	execute_command(args);
}
/***/
void search_and_execute(char **args)
{
	char *path = getenv("PATH");

	if (path)
	{
		char path_copy[MAX_INPUT_SIZE];
		char *dir = strtok(path_copy, ":");
		int found = 0;

		strcpy(path_copy, path);
		while (dir)
		{
			char command_path[MAX_INPUT_SIZE];

			snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);
			if (access(command_path, X_OK) == 0)
			{
				execute_external_command(args);
				found = 1;
				break;
			}
			dir = strtok(NULL, ":");
		}
		if (!found)
			print_command_not_found_error(args[0]);
	}
}
/***/
void execute_input(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		exit(0);
	else if (strcmp(args[0], "env") == 0)
		print_environment();
	else
	{
		if (is_absolute_path(args[0]))
			if (access(args[0], X_OK) == 0)
			{
				execute_external_command(args);
			} else
				print_permission_denied_error(args[0]);
			else
				search_and_execute(args);
	}
}
/***/
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execvp(args[0], args);
		perror("Error");
		exit(EXIT_FAILURE);
	} else if (pid > 0)
		wait(NULL);
	else
		perror("Fork failed");
}
