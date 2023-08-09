# include "shell.h"
/***/
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/***/
int main(int argc, char *argv[])
{
	if (argc > 1)
		non_interactive_mode(argv[1]);
	else
		interactive_mode();

	return (0);
}
/***/
void interactive_mode(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_INPUT_LENGTH];

	while (1)
	{
		display_prompt();

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		tokenize_input(input, args);

		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
				break;
			else
				execute_command(args);
		}
	}
}
/***/
void non_interactive_mode(const char *filename)
{
	FILE *file = fopen(filename, "r");
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_INPUT_LENGTH];

	if (!file)
	{
		perror("shell");
		exit(EXIT_FAILURE);
	}
	
	while (fgets(input, sizeof(input), file) != NULL)
	{	
		tokenize_input(input, args);

		if (args[0] != NULL && strcmp(args[0], "exit") == 0)
			break;
		execute_command(args);
	}
	fclose(file);
}
/***/
void tokenize_input(char *input, char **args)
{
	int arg_count = 0;

	args[arg_count] = strtok(input, " \t\n");
	while (args[arg_count] != NULL)
	{
		arg_count++;
		args[arg_count] = strtok(NULL, " \t\n");
	}
}
