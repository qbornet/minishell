#ifndef ERROR_H
# define ERROR_H
# define ERR_PARSER "Error: Syntax error\n"
# define ERR_COMMAND "Error: command not found\n"
# define ERR_FILE "Error: no such file\n"
# include <libft.h>

typedef enum e_error
{
	E_FILE = 1,
	E_PARSER,
	E_COMMAND = 127,
	E_MAX
}	t_error;

int	print_error(t_error);

#endif
