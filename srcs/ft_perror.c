#include "minishell.h"

static char	*internal_error(const int status)
{
	g_exit_status = 2;
	if (status == E_FORBIDDEN_0)
		return ("make sure not to use ) ( &\n");
	if (status == E_FORBIDDEN_1)
		return ("make sure not to use ||\n");
	if (status == E_TOK_CREA)
		return ("something went wrong in token creation\n");
	if (status == E_UNC_QUO)
		return ("unclosed quotes\n");
	if (status == E_SYNTAX)
		return ("syntax error near unexpected token ");
	return (NULL);
}

void	ft_perror(const char *s, const int code)
{
	int	status;

	if (code)
		status = code;
	else
		status = g_exit_status;
	if (!s || status == E_SYNTAX)
		write(2, "minishell", 10);
	else
		write(2, s, ft_strlen(s));
	write(2, ": ", 2);
	write(2, internal_error(status), ft_strlen(internal_error(status)));
	if (status == E_SYNTAX)
	{
		write(2, "`", 1);
		write(2, s, ft_strlen(s));
		write(2, "'\n", 2);
	}
}

int	ft_perror_ret(const char *s, const int code, const int rvalue)
{
	ft_perror(s, code);
	return (rvalue);
}
