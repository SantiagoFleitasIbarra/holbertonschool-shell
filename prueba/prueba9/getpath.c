# include "shell.h"
/***/
char *get_full_path(char *command)
{
	if (command[0] != '/')
	{
		char cwd[1024];

		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			char *full_path = malloc(strlen(cwd) + strlen(command) + 2);

			if (full_path != NULL)
			{
				strcpy(full_path, cwd);
				strcat(full_path, "/");
				strcat(full_path, command);
				return (full_path);
			}
			else
			{
				perror("malloc");
				return (NULL);
			}
		}
		else
		{
			perror("getcwd");
			return (NULL);
		}
	}
	else
		return (strdup(command));
}
