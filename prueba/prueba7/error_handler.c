# include "shell.h"
# include "error_handler.h"
/***/
void print_command_not_found_error(const char *command)
{
	fprintf(stderr, "./hsh: 1: %s: not found\n", command);
}
/***/
void print_permission_denied_error(const char *command)
{
	fprintf(stderr, "./hsh: 1: %s: Permission denied\n", command);
}
