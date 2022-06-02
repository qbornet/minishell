#include <minishell.h>

char	*ft_error_ret(char *str)
{
	free(str);
	return (NULL);
}
