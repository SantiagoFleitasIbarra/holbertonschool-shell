# ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H
# include "shell.h"
void print_command_not_found_error(const char *command);
void print_permission_denied_error(const char *command);
#endif
