#include "minishell.h"

static char	*error_message(int status)
{
	if (status == 127)
		return ("command not found\n");
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

void	ft_perror(const char *s)
{
	if (!s)
		write(2, "minishell", 10);
	else
		write(2, s, ft_strlen(s));
	write(2, ": ", 2);
	write(2, error_message(g_exit_status), ft_strlen(error_message(g_exit_status)));
	g_exit_status = 2;
}

void	ft_pcustom_error(const char *s, int code)
{

}
