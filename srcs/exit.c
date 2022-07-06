#include <minishell.h>

/* :0 */

static int	ft_isvalidargs(char *str)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		while (str[i] == '-' || str[i] == '+')
		{
			i++;
			count++;
		}
		if (count > 1 || !ft_isdigit(str[i]))
				return (0);
	}
	return (1);
}

static int	opt_exit(t_cmdblock *cmdblk, t_data **d_curr)
{
	size_t		i;
	char		*str;

	i = 0;
	while (cmdblk->cmd[++i])
	{
		str = ft_strdup(cmdblk->cmd[i]);
		if (!str)
			return (-1);
		if (!ft_isvalidargs(str)
				|| !ft_strcmp(str, "-9223372036854775809") || !ft_strcmp(str, "9223372036854775808"))
		{
			ft_putstr_fd("exit: numeric argument required '", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd("'", 2);
			free(str);
			ft_free_all(d_curr);
			exit(2);
		}
		free(str);
	}
	return (0);
}

void	ft_exit(t_data **d_curr)
{
	int				i;
	int				ret;
	unsigned char	status;

	status = g_exit_status;
	write(1, "exit\n", 5);
	ret = opt_exit((*d_curr)->cmdblk, d_curr);
	if (ret < 0)
		exit_group(d_curr);
	i = -1;
	while ((*d_curr)->cmdblk->cmd[++i])
	{
		if (i > 1)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			ft_free_all(d_curr);
			exit(1);
		}
	}
	if ((*d_curr)->cmdblk->cmd[1])
		status = ft_atoi((*d_curr)->cmdblk->cmd[1]);
	ft_free_all(d_curr);
	exit(status);
}
