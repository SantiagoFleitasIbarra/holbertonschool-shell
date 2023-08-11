# include "shell.h"
/**
 * handle_cd - implement the builtin command
 * @args: string arrangement
*/
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
/**
 * handle_help - implement the builtin command
*/
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
/**
 * handle_setenv - implement the builtin command
 * @args: string arrangement
*/
void handle_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}

	if (setenv(args[1], args[2], 1) == -1)
		perror("setenv");
	else
		printf("%s=%s\n", args[1], args[2]);
}
/**
 * handle_unsetenv - implement the builtin command
 * @args: string arrangement
*/
void handle_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return;
	}

	if (unsetenv(args[1]) == -1)
		fprintf(stderr, "Failed to unset environment variable: %s\n", args[1]);
}
