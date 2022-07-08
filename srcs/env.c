#include <minishell.h>

static int	opt_env(t_cmdblock *cmdblk)
{
	size_t	i;
	char	*var;

	i = 0;
	while (cmdblk->cmd[i])
	{
		var = ft_strdup(cmdblk->cmd[i]);
		if (!var)
			return (-1);
		if (ft_strchr(var, '-'))
		{
			ft_putstr_fd("env: no option for env '", 2);
			ft_putstr_fd(var, 2);
			ft_putendl_fd("'", 2);
			g_exit_status = 2;
			return (-1);
		}
		free(var);
		i++;
	}
	return (0);
}

int	ft_env(t_cmdblock *cmdblk, char **envp)
{
	int		i;

	if (!envp)
		return (0);
	if (opt_env(cmdblk) < 0)
		return (0);
	if (cmdblk->cmd[1] != NULL)
		return (ft_perror_ret(cmdblk->cmd[1], E_DENIED, -1));
	i = 0;
	while (envp[i])
	{
		if (write(STDOUT_FILENO, envp[i], ft_strlen(envp[i])) == -1)
			return (-1);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

/*
int	main(int ac, char **av, char **envp)
{
	if (ac != 1)
		return (-1);
	ft_env(envp);
	return (0);
}
*/
