#include <minishell.h>

static int	ft_checkalnum(char *var)
{
	size_t	i;

	i = -1;
	while (var[++i])
		if ((!ft_isalnum(var[i]) && var[i] != '=')  || var[i] != '_')
			return (0);
	return (1);
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
	if (ft_checkalnum(var))
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
