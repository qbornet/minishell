#include "minishell.h"

static int	open_first(int **pipes, t_cmdblock *cmdblock, int i)
{
	if (dup_out(3) < 0)
		return (-1);
	if (set_infile(cmdblock->infile) < 0)
		return (-1);
	if (ft_redirection_pipe_out(pipes[i], 1) < 0)
		return (-1);
	if (set_outfile(cmdblock->outfile) < 0)
		return (-1);
	return (0);
}

static int	open_last(int **pipes, t_cmdblock *cmdblock, int i)
{
	while (cmdblock->next)
		cmdblock = cmdblock->next;
	if (ft_redirection_pipe_in(pipes[i - 1], 0) < 0)
		return (-1);
	if (set_infile(cmdblock->infile) < 0)
		return (-1);
	if (dup_out(4) < 0)
		return (-1);
	if (set_outfile(cmdblock->outfile) < 0)
		return (-1);
	return (0);
}

static int	open_pipe(int **pipes, int i)
{
	if (ft_redirection_pipe_in(pipes[i - 1], 0) < 0)
		return (-1);
	if (ft_redirection_pipe_out(pipes[i], 1) < 0)
		return (-1);
	return (0);
}

static int	open_mid(int **pipes, t_cmdblock *cmdblock, int i)
{
	int			j;

	j = -1;
	while (++j != i)
		cmdblock = cmdblock->next;
	if (ft_redirection_pipe_in(pipes[i - 1], 0) < 0)
		return (-1);
	if (set_infile(cmdblock->infile) < 0)
		return (-1);
	if (ft_redirection_pipe_out(pipes[i], 1) < 0)
		return (-1);
	if (set_outfile(cmdblock->outfile) < 0)
		return (-1);
	return (0);
}

int	open_fd(int **pipes, t_cmdblock **avector, int pipes_len, int i)
{
	t_cmdblock	*cmdblock;

	cmdblock = *avector;
	if (i == 0)
	{
		if (open_first(pipes, cmdblock, i) < 0)
			return (-1);
	}
	else if (i == pipes_len)
	{
		if (open_last(pipes, cmdblock, i) < 0)
			return (-1);
	}
	else if (pipes_len > 2)
	{
		if (open_mid(pipes, cmdblock, i) < 0)
			return (-1);
	}
	else
	{
		if (open_pipe(pipes, i) < 0)
			return (-1);
	}
	return (0);
}
