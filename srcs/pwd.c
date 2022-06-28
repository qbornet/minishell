#include <minishell.h>

static int opt_pwd(t_cmdblock *cmdblk)
{
	size_t	i;
	char	*var;

	i = 1;
	while (cmdblk->cmd[i])
	{
		var = ft_strdup(cmdblk->cmd[i]);
		if (!var)
			return (-1);
		if (ft_strchr(var, '-'))
		{
			ft_putstr_fd("pwd: no option for pwd ", 2);
			ft_putendl_fd(var, 2);
			free(var);
			return (1);
		}
		i++;
		free(var);
	}
	return (0);
}

int	ft_pwd(t_cmdblock *cmdblk)
{
	int		ret;
	char	*cwd;

	ret = opt_pwd(cmdblk);
	if (ret)
		return (1);
	else if (ret < 0)
		return (-1);
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
