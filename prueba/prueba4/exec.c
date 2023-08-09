# include "shell.h"
/**
 * execute_command - manages the execution of external commands in the shell
 * @args: string arrangement
*/
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
/**
 * execute_input - executes a command provided as an argument
 * @args: string arrangement
*/
void execute_input(char **args)
{
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
	} else if (strcmp(args[0], "cd") == 0)
	{
		handle_cd(args);
	} else if (strcmp(args[0], "help") == 0)
	{
		handle_help();
	} else if (strcmp(args[0], "setenv") == 0)
	{
		handle_setenv(args);
	} else if (strcmp(args[0], "unsetenv") == 0)
	{
		handle_unsetenv(args);
	}
	else
	{
		if (is_absolute_path(args[0]))
		{
			if (access(args[0], X_OK) == 0)
				execute_command(args);
			else
				fprintf(stderr, "Command not found: %s\n", args[0]);
		} else
		{
			search_and_execute(args);
		}

	}
}
/**
 * search_and_execute - search for a command in the PATH locations
 * @args: an arrangement of strings
*/
void search_and_execute(char **args)
{
	char *path = getenv("PATH");

	if (args[0] == NULL)
		return;

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
		{
			if (strchr(args[0], '/') != NULL)
				fprintf(stderr, "%s: No such file or directory\n", args[0]);
			else if (dir == NULL)
				fprintf(stderr, "bash: %s: command not found\n",args[0]);
			else
				fprintf(stderr, "%s: Is a directory\n", args[0]);
		}
	}
}
/***/
void handle_cd(char **args)
{
	if (args[1] == NULL)
	{
		char *home_dir = getenv("HOME");

		if (home_dir != NULL)
		{
			if (chdir(home_dir) == -1)
				perror("cd");
		} else
			fprintf(stderr, "cd: $HOME not set\n");
	} else
	{
		struct stat path_stat;

		if (stat(args[1], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				if (chdir(args[1]) == -1)
					perror("cd");
			} else
				fprintf(stderr, "bash: cd: %s: Not a directory\n", args[1]);
		} else
			fprintf(stderr, "bash: cd: %s: No such file or directory\n", args[1]);
	}
}
/***/
void handle_help(void)
{
	printf("Simple Shell Help:\n");
	printf("  cd [DIRECTORY] - Change the current directory\n");
	printf("  help - Display help information\n");
	printf("  exit - Exit the shell\n");
	printf("  env - Print the environment\n");
	printf("  setenv VARIABLE VALUE - Set an environment variable\n");
	printf("  unsetenv VARIABLE - Unset an environment variable\n");
}
