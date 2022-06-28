#include <minishell.h>

/* :0 */

static void	opt_exit(t_cmdblock *cmdblk)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	while (cmdblk->cmd[++i])
	{
		str = ft_strdup(cmdblk->cmd[i]);
		if (!str)
			return ;
		j = -1;
		while (str[++j])
		{
			if (!ft_isdigit(str[j]))
			{
				ft_putstr_fd("exit: numeric argumenet required '", 2);
				ft_putstr_fd(str, 2);
				ft_putendl_fd("'", 2);
				free(str);
				break ;
			}
		}
		free(str);
	}
}

void	ft_exit(t_data **d_curr, int status)
{
	opt_exit((*d_curr)->cmdblk);
	write(1, "exit\n", 5);
	ft_free_all(d_curr);
	exit(status);
}
