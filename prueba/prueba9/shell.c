# include "shell.h"
/***/
int main(void)
{
	char input[MAX_INPUT_SIZE], *tokens[MAX_TOKENS], *token;

	while (1)
	{
		int token_count = 0, i;
		struct InternalCommand *internal_cmds = get_internal_commands();

		display_prompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
				perror("fgets"), exit(EXIT_FAILURE);
		}
		token = strtok(input, " \t\n");
		while (token != NULL && token_count < MAX_TOKENS)
		{
			tokens[token_count] = strdup(token), token_count++;
			token = strtok(NULL, " \t\n");
		}
		tokens[token_count] = NULL;
		for (i = 0; internal_cmds[i].name != NULL; i++)
		{
			if (strcmp(tokens[0], internal_cmds[i].name) == 0)
			{
				internal_cmds[i].function(tokens);
				break;
			}

		}
		if (internal_cmds[i].name == NULL)
			execute_command(tokens);
		for (i = 0; i < token_count; i++)
			free(tokens[i]);
	}
	return (0);
}
/***/
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
