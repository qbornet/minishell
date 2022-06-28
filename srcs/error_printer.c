#include "minishell.h"

static char	*error_message(int status)
{
	if (status == 501)
		return ("minishell: make sure not to use ) ( &\n");
	if (status == 502)
		return ("minishell: make sure not to use ||\n");
	if (status == 503 || status ==  504)
		return ("minishell: something went wrong in token creation\n");
	if (status == 505)
		return ("minishell: quotes unclosed\n");
	if (status == 506)
		return ("minishell: syntax error\n");
	return (NULL);
}

void	error_printer(void)
{
	write(2, error_message(g_exit_status), ft_strlen(error_message(g_exit_status)));
	g_exit_status = 2;
}
