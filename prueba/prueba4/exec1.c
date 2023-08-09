# include "shell.h"
/***/
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
/***/
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
