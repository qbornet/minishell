#include "minishell.h"

static char	*error_message(int status)
{
	if (status == 501)
		return ("lexer error: make sure not to use ) ( \\ ;\n");
	if (status == 502)
		return ("lexer error: make sure not to use ||\n");
	if (status == 503 || status ==  504)
		return ("lexer error: something wrong in token creation\n");
	return (NULL);
}

void	error_printer(void)
{
	write(2, error_message(g_exit_status), ft_strlen(error_message(g_exit_status)));
}
