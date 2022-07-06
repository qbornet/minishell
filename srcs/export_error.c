#include <minishell.h>

static int	ft_isword(int c)
{
	if (ft_isalnum(c) || c== '_')
		return (1);
	return (0);
}

static int	ft_checkalnum(char *var)
{
	char	*sub;
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	sub = ft_substr(var, 0, i);
	if (!sub)
		return (-1);
	else if (!sub[0])
	{
		free(sub);
		return (0);
	}
	i = -1;
	while (sub[++i])
	{
		if (!ft_isword(sub[i]))
		{
			free(sub);
			return (0);
		}
	}
	free(sub);
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


int	ft_checkvar_name(char *var, t_data **d_curr)
{
	int	ret;

	ret = ft_checkalnum(var);
	if (ret < 0)
		exit_group(d_curr);
	else if (!ret)
		return (1);
	return (0);
}

int	ft_printerror(char *var)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(" : not a valid indentifier\n", 2);
	free(var);
	return (1);
}
