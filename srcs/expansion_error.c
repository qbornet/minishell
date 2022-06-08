#include <minishell.h>

int	ft_free_expan_error(t_data **d_curr)
{
	int		i;
	t_data	*frame;

	frame = *d_curr;
	close(frame->std_fd.stdin);
	close(frame->std_fd.stdout);
	close(frame->std_fd.stderr);
	ft_strclear(&frame->strlst, &free);
	ft_tokenclear(&frame->tokenlst, &free);
	ft_treeclear(frame->root, &free);
	i = -1;
	while (frame->envp[++i])
		free(frame->envp[i]);
	i = -1;
	while (frame->var_pool[++i])
		free(frame->var_pool[i]);
	free(frame->envp);
	free(frame->var_pool);
	free(frame);
	return (-1);
}
