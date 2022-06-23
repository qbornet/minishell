#include "minishell.h"

int	ft_free_env(char **old)
{
	long	i;

	i = -1;
	while (old[++i])
		if (old[i])
			free(old[i]);
	free(old);
	return (0);
}

int	ft_free_err(char **old, char **new)
{
	long	i;

	if (old)
	{
		i = -1;
		while (old[++i])
			if (old[i])
				free(old[i]);
		free(old);
	}
	if (new)
	{
		i = -1;
		while (new[++i])
			if (new[i])
				free(new[i]);
		free(new);
	}
	return (1);
}
