#include <minishell.h>

int	ft_check_pool(char *str, char **pool, int res)
{
	size_t	i;

	i = 0;
	if (res >= 0)
	{
		free(pool[res]);
		pool[res] = ft_strdup(str);
		if (!pool[res])
			return (-1);
		return (1);
	}
	else
	{
		while (pool[i])
			i++;
		pool[i] = ft_strdup(str);
		if (!pool)
			return (-1);
		return (1);
	}
	return (0);
}
