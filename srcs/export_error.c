#include <minishell.h>

int	ft_dup_error(char **arr)
{
	size_t	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (-1);
}
