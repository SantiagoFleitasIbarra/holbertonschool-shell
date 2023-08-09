# include "shell.h"
# include "error_handler.h"
/***/
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/***/
int is_absolute_path(char *command)
{
	return (strchr(command, '/') != NULL);
}
/***/
void handle_noninteractive_mode(void)
{
	char input[MAX_INPUT_SIZE];

	while (fgets(input, sizeof(input), stdin))
	{
		input[strcspn(input, "\n")] = '\0';
		tokenize_input(input, args);
		if (args[0] != NULL)
			execute_input(args);
	}
}
/***/
void print_environment(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
/***/
int main(void)
{
	if (!isatty(STDIN_FILENO))
		handle_noninteractive_mode();
	else
	{
		while (1)
		{
			char input[MAX_INPUT_SIZE];
			char *args[MAX_INPUT_SIZE / 2 + 1];

			display_prompt();
			if (fgets(input, sizeof(input), stdin) == NULL)
			{
				printf("\n");
				break;
			}
			input[strcspn(input, "\n")] = '\0';
			tokenize_input(input, args);
			if (args[0] != NULL)
				execute_input(args);
		}
	}
	return (0);
}
