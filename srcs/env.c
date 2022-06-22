#include "minishell.h"

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (write(STDOUT_FILENO, envp[i], ft_strlen(envp[i])) == -1)
			return (1);
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
