# include "shell.h"
/***/
char *get_absolute_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (strdup(command));
	return (NULL);
}
/***/
char *search_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	if (path == NULL)
		return (NULL);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}
	while (token != NULL)
	{
		char *full_path = malloc(strlen(token) + strlen(command) + 2);

		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
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
		waitpid(pid, &status, 0);
}
