# include "shell.h"
/**
 * display_prompt - displays the prompt indicator in the shell interface
*/
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/**
 * is_absolute_path - checks whether a command is an absolute path or not
 * @command: command to be executed
 * Return: an integer value
 * 1, means that the command is an absolute path. If it returns
 * 0, the command is not an absolute path
*/
int is_absolute_path(char *command)
{
	return (strchr(command, '/') != NULL);
}
/**
 * handle_noninteractive_mode - handles command execution in non-interactive
 * mode
*/
void handle_noninteractive_mode(void)
{
	char input[MAX_INPUT_SIZE];

	while (fgets(input, sizeof(input), stdin))
	{
		char *args[MAX_INPUT_SIZE / 2 + 1];

		input[strcspn(input, "\n")] = '\0';
		tokenize_input(input, args);
		if (args[0] != NULL)
			execute_input(args);
	}
}
/**
 * tokenize_input - splits an input string into tokens
 * @input: input string
 * @args: string arrangement
*/
void tokenize_input(char *input, char **args)
{
	char *token = strtok(input, " ");
	int i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}
/**
 * main - main program entry
 * Return: 0 Always (Success)
*/
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
