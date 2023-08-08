# include "main.h"
/***/
void display_prompt()
{
	printf("$ ");
	fflush(stdout);
}
/***/
int main()
{
	char input[MAX_INPUT_SIZE], *args[MAX_INPUT_SIZE / 2 + 1];
	char *token = strtok(input, " ");
	int i = 0;

	while (1)
	{
		display_prompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		if (args[0] == NULL)
			continue;
		if (strcmp(args[0], "exit") == 0)
			exit(0);
		else if (strcmp(args[0], "env") == 0)
		{
			char **env = environ;

			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
		} else
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
						execute_command(args);
						found = 1;
						break;
					}
					dir = strtok(NULL, ":");
				}
				if (!found)
					printf("Command not found: %s\n", args[0]);
			}
		}
	}
	return (0);
}
