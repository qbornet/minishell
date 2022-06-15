#include "minishell.h"

static int	open_first(t_data **frame, int **pipes, t_cmdblock *cmdblock, int i)
{
	if (dup_in(cmdblock->std_fd->stdin) < 0)
		return (-1);
	if (set_infile(frame, cmdblock->infile) < 0)
		return (-1);
	if (ft_redirection_pipe_out(pipes[i], 1) < 0)
		return (-1);
	if (set_outfile(cmdblock->outfile) < 0)
		return (-1);
	return (0);
}

static int	open_last(t_data **frame, int **pipes, t_cmdblock *cmdblock, int i)
{
	while (cmdblock->next)
		cmdblock = cmdblock->next;
	if (ft_redirection_pipe_in(pipes[i - 1], 0) < 0)
		return (-1);
	if (set_infile(frame, cmdblock->infile) < 0)
		return (-1);
	if (dup_out(cmdblock->std_fd->stdout) < 0)
		return (-1);
	if (set_outfile(cmdblock->outfile) < 0)
		return (-1);
	return (0);
}

static int	open_mid(t_data **frame, int **pipes, t_cmdblock *cmdblock, int i)
{
	cmdblock = next_cmdb(i, &cmdblock);
	if (ft_redirection_pipe_in(pipes[i - 1], 0) < 0)
		return (-1);
	if (set_infile(frame, cmdblock->infile) < 0)
		return (-1);
	if (ft_redirection_pipe_out(pipes[i], 1) < 0)
		return (-1);
	if (set_outfile(cmdblock->outfile) < 0)
		return (-1);
	return (0);
}

int	open_fd(int **pipes, t_data **frame, int pipes_len, int i)
{
	t_cmdblock	*cmdblock;

	if (pipes_len == 0)
		return (0);
	cmdblock = (*frame)->cmdblk;
	if (i == 0)
	{
		if (open_first(frame, pipes, cmdblock, i) < 0)
			return (-1);
	}
	else if (i == pipes_len)
	{
		if (open_last(frame, pipes, cmdblock, i) < 0)
			return (-1);
	}
	else
	{
		if (open_mid(frame, pipes, cmdblock, i) < 0)
			return (-1);
	}
	return (0);
}
