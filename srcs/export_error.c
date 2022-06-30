#include <minishell.h>

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

	i = -1;
	flag = 0;
	while (var[++i])
		if (var[i] == '_')
			flag = 1;
	if (ft_isalnum(var) && flag)
		return (1);
	else if (ft_isalnum(var) || flag)
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
