#include <minishell.h>

static char	*get_env_home(char **env)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "HOME=", 5))
		i++;
	if (env[i] && !ft_strncmp(env[i], "HOME=", 5))
		home = ft_strdup(env[i] + 5);
	return (home);
}

static int	chdir_home(char *home)
{
	if (chdir(home) < 0)
	{
		free(home);
		return (-1);
	}
	free(home);
	return (0);
}

int	ft_cd(const t_cmdblock *cmdblock, char **envp)
{
	char	*home;

	if (cmdblock->cmd[1] && cmdblock->cmd[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	home = get_env_home(envp);
	if (!home && !cmdblock->cmd[1])
		return (0);
	if (!cmdblock->cmd[1] && home)
	{
		if (chdir_home(home) < 0)
			return (-1);
		return (0);
	}
	if (chdir(cmdblock->cmd[1]) < 0)
	{
		write(2, "cd: ", 4);
		write(2, cmdblock->cmd[1], ft_strlen(cmdblock->cmd[1]));
		write(2, ": Not a directory\n", 19);
		return (1);
	}
	return (0);
}
