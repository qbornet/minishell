#include "minishell.h"

int	ft_env(t_cmdblock *cmdblk, char **envp)
{
	int	i;

	if (!envp)
		return (0);
	if (cmdblk->cmd[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
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
