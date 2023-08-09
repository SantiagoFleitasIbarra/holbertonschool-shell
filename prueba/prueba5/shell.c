# include "shell.h"
/***/
void print_prompt(void)
{
	printf("$ ");
}
/***/
int main(void)
{
	char *buffer = NULL;
	size_t length = 0;
	ssize_t read_chars;

	while (1)
	{
		print_prompt();
		read_chars = getline(&buffer, &length, stdin);
		if (read_chars == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("getline");
			exit(EXIT_FAILURE);
		}
		if (buffer[read_chars - 1] == '\n')
			buffer[read_chars - 1] = '\0';
		execute_command(buffer);
	}
	free(buffer);

	return (0);
}
