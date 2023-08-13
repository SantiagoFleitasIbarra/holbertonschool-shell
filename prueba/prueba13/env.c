#include "shell.h"
/***/
void compare_env_and_environ(char **env)
{
	printf("Address of env: %p\n", (void *)env);
	printf("Address of environ: %p\n", (void *)environ);
	if (env == environ)
		printf("env and environ are the same.\n");
	else
		printf("env and environ are different.\n");
}
/***/
void printenv_with_environ(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
/***/
int _setenv(const char *name, const char *value, int overwrite)
{
	char *existing = _getenv(name);
	size_t new_var_len = strlen(name) + strlen(value) + 2;
	char *new_var = (char *)malloc(new_var_len);

	if (!name || strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (existing && !overwrite)
		return (0);
	if (!new_var)
		return (-1);
	snprintf(new_var, new_var_len, "%s=%s", name, value);
	if (putenv(new_var) != 0)
	{
		free(new_var);
		return (-1);
	}
	return (0);
}
/***/
int _unsetenv(const char *name)
{
	char **env_var = environ;

	if (!name || strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	while (*env_var)
	{
		if (strncmp(*env_var, name, strlen(name)) == 0 && (*env_var)[strlen(name)] == '=')
		{
			char **src = env_var + 1;
			char **dst = env_var;

			while (*src)
			{
				*dst = *src;
				src++;
				dst++;
			}
			*dst = NULL;
			return (0);
		}
		env_var++;
	}
	return (0);
}
