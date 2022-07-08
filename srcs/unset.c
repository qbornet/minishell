#include "minishell.h"

/* TODO: ✔️ 
 * - Doit unset toute les variables qui ont le meme nom dans var_pool et envp */

static int	ft_isvalid_varname(char *var)
{
	size_t	i;

	i = -1;
	if (var[0] == '\0' || ft_isdigit(var[0]))
		return (0);
	while (var[++i])
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
	return (1);
}

static long	index_match(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(var, envp[i], ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}

static long	index_match_vpool(char *var, char **var_pool)
{
	int		i;

	i = 0;
	while (var_pool[i])
	{
		if (!ft_strncmp(var, var_pool[i], ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_unset_var(t_data **d_curr, char *var)
{
	long	index_envp;
	long	index_vpool;

	if (!ft_isvalid_varname(var))
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("' : not a valid indentifier\n", 2);
		g_exit_status = 1;
		return (0);
	}
	index_envp = index_match(var, (*d_curr)->envp);
	index_vpool = index_match_vpool(var, (*d_curr)->var_pool);
	if (ft_recreate_envp(&(*d_curr)->envp, index_envp) < 0)
		return (-1);
	if (ft_recreate_vpool(&(*d_curr)->var_pool, index_vpool) < 0)
		return (-1);
	return (0);
}

int	ft_unset(t_data **frame, t_cmdblock *cmdblock)
{
	int			i;
	char		*var;

	i = 1;
	while (cmdblock->cmd[i])
	{
		var = ft_strdup(cmdblock->cmd[i]);
		if (!var)
			return (-1);
		if (ft_strchr(var, '-') && ft_strlen(var) == 2)
		{
			ft_putstr_fd("unset: no option for unset ", 2);
			ft_putendl_fd(var, 2);
			free(var);
			g_exit_status = 2;
			return (-1);
		}
		if (ft_unset_var(frame, cmdblock->cmd[i]) < 0)
			return (-1);
		i++;
		free(var);
	}
	return (0);
}

/*

int	main(int ac, char **av, char **envp)
{
	char	*str;

	if (ac != 2)
		return (-1);
	str = strdup(av[1]);
	printf("-----------------------------------\n");
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	ft_unset(str, &envp);
	printf("-----------------------------------\n");
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	for (int i = 0; envp[i]; i++)
		if (envp[i])
			free(envp[i]);
	free(envp);
	free(str);
	return (0);
}
*/
