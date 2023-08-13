#include "shell.h"
/***/
int main(int argc, char *argv[], char *env[])
{
	char *var = _getenv("PATH");
	PathNode *path_list = build_path_list();
	PathNode *current = path_list;

	(void)argc, (void)argv;
	printenv_with_environ();

	compare_env_and_environ(env);

	if (var)
		printf("Value of PATH: %s\n", var);
	else
		printf("PATH variable not found.\n");

	print_path_directories();

	while (current)
	{
		printf("Directory: %s\n", current->directory);
		current = current->next;
	}
	_setenv("MY_VARIABLE", "12345", 1);
	_unsetenv("MY_VARIABLE");

	return (0);
}
/***/
void print_path_directories(void)
{
	char *path = _getenv("PATH");

	if (path)
	{
		char *token = strtok(path, ":");

		while (token)
		{
			printf("%s\n", token);
			token = strtok(NULL, ":");
		}
	}
}
/***/
PathNode *build_path_list(void)
{
	char *path = _getenv("PATH");
	PathNode *head = NULL;
	PathNode *current = NULL;

	if (path)
	{
		char *token = strtok(path, ":");

		while (token)
		{
			PathNode *node = (PathNode *)malloc(sizeof(PathNode));
			if (!node)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			node->directory = strdup(token);
			node->next = NULL;

			if (!head)
			{
				head = node;
				current = node;
			}
			else
			{
				current->next = node;
				current = node;
			}
			token = strtok(NULL, ":");
		}
	}
	return (head);
}
