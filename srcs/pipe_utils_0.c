#include "minishell.h"

int	ft_redirection_less(char *infile, int *pd)
{
	int		fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		return (standard_error(infile));
	if (dup_inout(fd, pd[1]) == -1)
		return (-1);
	if (close(fd) == -1)
		return (standard_error("pipe_in close fd"));
	if (close_pipe(pd) == -1)
		return (standard_error("pipe_in close pd"));
	return (0);
}

int	ft_redirection_pipe(int *pd_in, int *pd_out)
{
	if (dup_inout(pd_in[0], pd_out[1]) == -1)
		return (standard_error("pipe_mid dup_inout"));
	if (close_pipe(pd_in) == -1)
		return (standard_error("pipe_mid close pd_in"));
	if (close_pipe(pd_out) == -1)
		return (standard_error("pipe_mid close pd_out"));
	return (0);
}

int	ft_redicrection_great(int *pd, char *outfile)
{
	int		fd;

	if (unlink(outfile) == -1)
		errno = 0;
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (standard_error(outfile));
	if (dup_inout(pd[0], fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (standard_error("pipe_out fd"));
	if (close_pipe(pd) == -1)
		return (standard_error("pipe_out close pd"));
	return (0);
}

int	ft_redicrection_dgreat(int *pd, char *outfile)
{
	int		fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (standard_error(outfile));
	if (dup_inout(pd[0], fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (standard_error("pipe_out fd"));
	if (close_pipe(pd) == -1)
		return (standard_error("pipe_out close pd"));
	return (0);
}

int	open_fd(int **pipes, t_cmdblock **avector, int pipes_len, int i)
{
	t_cmdblock	*cmdblock;

	cmdblock = *avector;
	if (i == 0)
	{
		if (ft_redirection_less(cmdblock->infile->str, pipes[i]) == -1)
			return (-1);
	}
	else if (i == pipes_len)
	{
		while (cmdblock->next)
			cmdblock = cmdblock->next;
		if (ft_redicrection_great(pipes[i - 1], cmdblock->outfile->str) == -1)
			return (-1);
	}
	else
	{
		if (ft_redirection_pipe(pipes[i - 1], pipes[i]) == -1)
			return (-1);
	}
	return (0);
}
