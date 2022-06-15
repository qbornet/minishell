#include <minishell.h>

int	exit_group(t_data **d_curr)
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
	exit(errno);
}

void	ft_null_reset(t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	frame->lenlst = NULL;
	frame->cmdblk = NULL;
	frame->strlst = NULL;
	frame->tokenlst = NULL;
	frame->root = NULL;
	frame->cmd_pool = NULL;
	*d_curr = frame;
}

int	free_redoo(t_data **d_curr, char *str)
{
	t_data	*frame;
	
	frame = *d_curr;
	free(str);
	ft_lenclear(&frame->lenlst);
	ft_cmdclear(&frame->cmdblk);
	ft_strclear(&frame->strlst, &free);
	ft_tokenclear(&frame->tokenlst, &free);
	ft_treeclear(frame->root, &free);
	ft_free_cpool(frame->cmd_pool);
	ft_null_reset(&frame);
	errno = 0;
	return (0);
}

int	start(char **envp)
{

	t_data	*frame;

	frame = ft_calloc(1, sizeof(t_data));
	if (!frame)
		return (-1);
	frame->std_fd = ft_calloc(1, sizeof(t_termstd));
	if (!frame->std_fd)
		return(exit_group(&frame));
	frame->std_fd->stdin = dup(STDIN_FILENO);
	frame->std_fd->stdout = dup(STDOUT_FILENO);
	if (frame->std_fd->stdin == -1 || frame->std_fd->stdin == -1)
		return (exit_group(&frame));
	frame->envp = ft_envp(envp);
	if (!frame->envp)
		return (exit_group(&frame));
	if (start_prompt(&frame) < 0)
		return (exit_group(&frame));
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		status;

	(void)ac;
	(void)av;
	pid = fork();
	if (pid == 0)
	{
		execve("/bin/clear", ((char *[]){"clear", NULL}), envp);
		return (0);
	}
	else if (pid == -1)
		return (0);
	else
	{
		waitpid(pid, &status, 0);
		start(envp);
	}
	return (0);
}
