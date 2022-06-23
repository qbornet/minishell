#include "minishell.h"

static int	open_first(int **pipes, t_cmdblock *cmdblock, int i)
{
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
	if (set_outfile(cmdblock->outfile) < 0)
		return (-1);
	return (0);
}

static int	open_mid(int **pipes, t_cmdblock *cmdblock, int i)
{
	cmdblock = next_cmdb(i, &cmdblock);
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

static int	ft_open(t_cmdblock *cmdblock)
{
	if (set_infile(cmdblock->infile) < 0)
		return (-1);
	if (set_outfile(cmdblock->outfile) < 0)
		return (-1);
	return (0);
}

int	open_fd(t_process *pr, t_cmdblock *cmdblock, int i)
{
	int	pipes_len;

	pipes_len = pr->len_cmdb - 1;
	if (pipes_len == 0)
	{
		if (ft_open(cmdblock) < 0)
			return (-1);
	}
	else if (i == 0)
	{
		if (open_first(pr->pipes, cmdblock, i) < 0)
			return (-1);
	}
	else if (i == pipes_len)
	{
		if (open_last(pr->pipes, cmdblock, i) < 0)
			return (-1);
	}
	else
	{
		if (open_mid(pr->pipes, cmdblock, i) < 0)
			return (-1);
	}
	return (0);
}
