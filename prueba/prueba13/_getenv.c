#include "shell.h"
/***/
char *_getenv(const char *name)
{
	int i = 0;

	while (environ[i])
	{
		char *entry = environ[i];

		if (strncmp(entry, name, strlen(name)) == 0 && entry[strlen(name)] == '=')
			return (entry + strlen(name) + 1);
		i++;
	}
	return (NULL);
}
