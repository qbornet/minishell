#include <minishell.h>

static int	is_metachar(char c)
{
	if (c == '(' || c == ')'
			|| c == '?'
			|| c == '$'
			|| c == '.'
			|| c == '-'
			|| c == '\\'
			|| c == '!'
			|| c == '\"'
			|| c == '\''
			|| (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_dup_error(char **arr)
{
	size_t	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (-1);
}

int	ft_checkvar_name(char *var)
{
	int		flag;
	size_t	i;

	i = 0;
	while (var[i])
		if (is_metachar(var[i]))
			flag = 1;
	if (((ft_strchr(var, '=') || !ft_strchr(var, '=')) && var[0] != '=') && !flag)
		return (1);
	return (0);
}

int	ft_printerror(char *var)
{
	ft_putstr_fd("minishell: export:", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(": not a valid indentifier\n", 2);
	return (1);
}
