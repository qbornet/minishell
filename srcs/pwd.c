#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cwd)
	{
		if (write(1, cwd, ft_strlen(cwd)) < 0)
			return (-1);
		if (write(1, "\n", 1) < 0)
			return (-1);
		free(cwd);
		return (0);
	}
	return (-1);
}
