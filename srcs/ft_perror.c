#include "minishell.h"

static char	*internal_error(const int status)
{
	if (status == 127)
		return ("command not found\n");
	if (status == 501)
		return ("make sure not to use ) ( &\n");
	if (status == 502)
		return ("make sure not to use ||\n");
	if (status == 503 || status ==  504)
		return ("something went wrong in token creation\n");
	if (status == 505)
		return ("quotes unclosed\n");
	if (status == 506)
		return ("syntax error\n");
	return (NULL);
}

void	ft_perror(const char *s, const int code)
{
	int	status;

	if (code)
		status = code;
	else
		status = g_exit_status;
	if (!s)
		write(2, "minishell", 10);
	else
		write(2, s, ft_strlen(s));
	write(2, ": ", 2);
	write(2, internal_error(status), ft_strlen(internal_error(status)));
	g_exit_status = 2;
}
