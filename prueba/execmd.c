#include "shell.h"
/***/
void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;

	if (argv && argv[0])
	{
		command = argv[0];
		actual_command = get_location(command);
		if (strcmp(command, "exit") == 0)
			exit(0);
		if (actual_command)
		{
			if (execve(actual_command, argv, NULL) == -1)
			{
				perror("Error:");
				exit(1);
			}
		} else
		{
			printf("bash: %s: command not found\n", command);
			exit(1);
		}
	}
}
