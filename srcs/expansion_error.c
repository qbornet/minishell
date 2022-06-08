#include <minishell.h>

static void	ft_free_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

static void ft_free_cpool(char ***cpool)
{
	size_t	i;

	i = 0;
	while (cpool[i])
		free(cpool[i++]);
	free(cpool);
}

static void	ft_free_vpool(char **var_pool)
{
	int	i;

	i = -1;
	while (var_pool[++i])
		free(var_pool[i]);
	free(var_pool);
}

int	ft_free_expan_error(t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	close(frame->std_fd.stdin);
	close(frame->std_fd.stdout);
	close(frame->std_fd.stderr);
	ft_lenclear(&frame->lenlst);
	ft_strclear(&frame->strlst, &free);
	ft_tokenclear(&frame->tokenlst, &free);
	ft_treeclear(frame->root, &free);
	ft_free_cpool(frame->cmd_pool);
	ft_free_vpool(frame->var_pool);
	ft_free_envp(frame->envp);
	free(frame);
	return (-1);
}
