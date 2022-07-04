#include <minishell.h>

/* :0 */

static int	opt_exit(t_cmdblock *cmdblk)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	while (cmdblk->cmd[++i])
	{
		str = ft_strdup(cmdblk->cmd[i]);
		if (!str)
			return (-1);
		j = -1;
		while (str[++j])
		{
			if (!ft_isdigit(str[j]) || (str[j] == '-' && !ft_isdigit(str[j + 1])))
			{
				ft_putstr_fd("exit: numeric argument required '", 2);
				ft_putstr_fd(str, 2);
				ft_putendl_fd("'", 2);
				free(str);
				return (1);
			}
		}
		free(str);
	}
	return (0);
}

void	ft_exit(t_data **d_curr)
{
	int				ret;
	unsigned char	status;

	status = 0;
	write(1, "exit\n", 5);
	ret = opt_exit((*d_curr)->cmdblk);
	if (ret < 0)
		exit_group(d_curr);
	if (ret)
		exit_group(d_curr);
	if ((*d_curr)->cmdblk->cmd[2] != NULL)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	if ((*d_curr)->cmdblk->cmd[1])
		status = ft_atoi((*d_curr)->cmdblk->cmd[1]);
	ft_free_all(d_curr);
	exit(status);
}
