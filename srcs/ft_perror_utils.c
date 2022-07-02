#include <minishell.h>

static char	*classic_error(const int status)
{
	g_exit_status = status;
	if (status == E_NOT_FOUND)
		return ("command not found\n");
	if (status == E_NOT_EXIST)
		return ("No such file or directory\n");
	if (status == E_IS_DIR)
		return ("Is a directory\n");
	if (status == E_DENIED)
		return ("Permission denied\n");
	return (NULL);
}

char	*internal_error(const int status)
{
	if (status < 500)
		return (classic_error(status));
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

int	err_msg(const char *s, const int len, const int code)
{
	char			*err_msg;

	err_msg = ft_calloc(len + 1, sizeof(char));
	if (!err_msg)
		return (-1);
	ft_strlcpy(err_msg, s, len + 1);
	ft_perror(err_msg, code);
	free(err_msg);
	return (1);
}
