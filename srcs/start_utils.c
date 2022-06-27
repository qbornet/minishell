#include <minishell.h>

void	ft_free_all(t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	ft_lenclear(&frame->lenlst);
	ft_strclear(&frame->strlst, &free);
	ft_cmdclear(&frame->cmdblk);
	ft_tokenclear(&frame->tokenlst, &free);
	ft_treeclear(frame->root, &free);
	ft_free_cpool(frame->cmd_pool);
	ft_free_vpool(frame->var_pool);
	ft_free_envp(frame->envp);
	free(frame->std_fd);
	free(frame);
	close_allfd();
}

int	ft_addlevel(char ***envp_curr)
{
	int		num;
	char	**envp;
	size_t	i;
	size_t	j;

	i = -1;
	envp = *envp_curr;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "SHLVL", 5))
			break ;
	if (!envp[i])
		return (0);
	j = 0;
	while (envp[i][j] != '=')
		j++;
	num = ft_atoi(&envp[i][++j]);
	num++;
	free(envp[i]);
	envp[i] = ft_strjoin("SHLVL=", ft_itoa(num));
	if (!envp[i])
		return (-1);
	*envp_curr = envp;
	return (0);
}
