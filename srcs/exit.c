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
			if (!ft_isdigit(str[j]))
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

void	ft_exit(t_data **d_curr, int status)
{
	int	ret;

	ret = opt_exit((*d_curr)->cmdblk);
	if (ret < 0)
		exit_group(d_curr);
	write(1, "exit\n", 5);
	if (ret)
		exit_group(d_curr);
	ft_free_all(d_curr);
	exit(status);
}
