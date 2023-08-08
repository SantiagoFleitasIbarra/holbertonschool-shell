#include "shell.h"
/***/
char *get_location(char *command)
{
	char *path = getenv("PATH");
	struct stat buffer;

	if (path)
	{
	char *path_copy = strdup(path), *path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		size_t command_length = strlen(command);
		size_t directory_length = strlen(path_token);
		char *file_path = malloc(directory_length + command_length + 2);

		if (!file_path)
		{
			perror("Error:");
			free(path_copy);
			return (NULL);
		}
		snprintf(file_path, directory_length + command_length + 2, "%s/%s",
				path_token, command);
		if (stat(file_path, &buffer) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		else
		{
		free(file_path);
		path_token = strtok(NULL, ":");
		}
	}
	free(path_copy);
	}
	if (stat(command, &buffer) == 0)
		return (strdup(command));
	return (NULL);
}
