#ifndef ERROR_H
# define ERROR_H
# define ERR_PARSER "Error: Syntax error\n"
# define ERR_COMMAND "Error: command not found\n"
# include <libft.h>

typedef enum e_error
{
	E_PARSER = 2,
	E_COMMAND = 127,
	E_MAX
}	t_error;

int	print_error(t_error);

#endif
