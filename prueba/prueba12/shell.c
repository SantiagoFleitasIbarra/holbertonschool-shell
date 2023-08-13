#include "shell.h"
/***/
int main(int argc, char *argv[])
{
	char input[MAX_INPUT_SIZE];
	char *tokens[MAX_INPUT_SIZE];
	int tokenCount;

	if (argc == 1)
	{
		while (1)
		{
			printf("$ ");
			if (fgets(input, sizeof(input), stdin) == NULL)
			{
				printf("\n");
				break;
			}

			input[strcspn(input, "\n")] = '\0';

			tokenizeInput(input, tokens, &tokenCount);

			if (tokenCount == 0)
				continue;

			executeCommand(tokens, tokenCount);
		}
	} else if (argc == 2)
	{
		FILE *inputFile = fopen(argv[1], "r");

		if (inputFile == NULL)
		{
			perror("simple_shell");
			return (EXIT_FAILURE);
		}
		while (fgets(input, sizeof(input), inputFile))
		{
			input[strcspn(input, "\n")] = '\0';
			tokenizeInput(input, tokens, &tokenCount);
			if (tokenCount == 0)
				continue;
			executeCommand(tokens, tokenCount);
		}
		fclose(inputFile);
	}
	return (0);
}
