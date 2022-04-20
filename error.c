#include "error.h"

int	print_error(t_error code)
{
	static char	*str[E_MAX];

	str[E_FILE] = ERR_FILE;
	str[E_PARSER] = ERR_PARSER;
	str[E_COMMAND] = ERR_COMMAND;
	write(2, str[code], ft_strlen(str[code]));
	return (code);
}

int	main(void)
{
	print_error(E_PARSER);
	print_error(E_COMMAND);
	return (0);
}
