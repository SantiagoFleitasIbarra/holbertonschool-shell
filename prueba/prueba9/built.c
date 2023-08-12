# include "shell.h"
/***/
void cd_command(char **args)
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
	else
	{
		fprintf(stderr, "cd: missing argument\n");
	}
}
/***/
void exit_command(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	exit(0);
}
/***/
void env_command(char **args)
{
	char **env = environ;

	(void)args;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
