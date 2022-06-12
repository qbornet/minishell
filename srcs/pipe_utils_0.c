#include "minishell.h"

int	ft_redirection_less(char *infile)
{
	int		fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		return (standard_error(infile));
	if (dup_in(fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (standard_error("pipe_in close fd"));
	return (0);
}

int	ft_redirection_pipe(int *pd_in, int *pd_out)
{
	if (dup_in(pd_in[0]) == -1)
		return (-1);
	if (close_pipe(pd_in) == -1)
		return (standard_error("pipe_mid close pd_in"));
	if (dup_out(pd_out[1]) == -1)
		return (-1);
	if (close_pipe(pd_out) == -1)
		return (standard_error("pipe_mid close pd_out"));
	return (0);
}

int	ft_redicrection_great(char *outfile)
{
	int		fd;

	if (unlink(outfile) == -1)
		errno = 0;
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (standard_error(outfile));
	if (dup_out(fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (standard_error("pipe_out fd"));
	return (0);
}

int	ft_redicrection_dgreat(int *pd, char *outfile)
{
	int		fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (standard_error(outfile));
	if (dup_in(pd[0]) == -1)
		return (-1);
	if (close_pipe(pd) == -1)
		return (standard_error("pipe_out close pd"));
	if (dup_out(fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (standard_error("pipe_out fd"));
	return (0);
}

int	open_fd(int **pipes, t_cmdblock **avector, int pipes_len, int i)
{
	int			j;
	t_cmdblock	*cmdblock;
	t_redirlist	*infile;
	t_redirlist	*outfile;

	cmdblock = *avector;
	if (i == 0)
	{
		infile = cmdblock->infile;
		while (infile)
		{
			if (ft_redirection_less(infile->str) == -1)
				return (-1);
			infile = infile->next;
		}
		if (dup_out(pipes[i][1]) == -1)
			return (-1);
		if (close_pipe(pipes[i]) == -1)
			return (standard_error("pipe_in close pd"));
		outfile = cmdblock->outfile;
		while (outfile)
		{
			if (ft_redicrection_great(outfile->str) == -1)
				return (-1);
			outfile = outfile->next;
		}
	}
	else if (i == pipes_len)
	{
		while (cmdblock->next)
			cmdblock = cmdblock->next;
		if (dup_in(pipes[i - 1][0]) == -1)
			return (-1);
		if (close_pipe(pipes[i - 1]) == -1)
			return (standard_error("pipe_out close pd"));
		infile = cmdblock->infile;
		while (infile)
		{
			if (ft_redirection_less(infile->str) == -1)
				return (-1);
			infile = infile->next;
		}
		outfile = cmdblock->outfile;
		while (outfile)
		{
			if (ft_redicrection_great(outfile->str) == -1)
				return (-1);
			outfile = outfile->next;
		}
	}
	else
	{
		j = -1;
		while (++j != i)
			cmdblock = cmdblock->next;
		if (dup_in(pipes[i - 1][0]) == -1)
			return (-1);
		if (close_pipe(pipes[i - 1]) == -1)
			return (standard_error("pipe_mid close pd_in"));
		infile = cmdblock->infile;
		while (infile)
		{
			if (ft_redirection_less(infile->str) == -1)
				return (-1);
			infile = infile->next;
		}
		if (dup_out(pipes[i][1]) == -1)
			return (-1);
		if (close_pipe(pipes[i]) == -1)
			return (standard_error("pipe_mid close pd_out"));
		outfile = cmdblock->outfile;
		while (outfile)
		{
			if (ft_redicrection_great(outfile->str) == -1)
				return (-1);
			outfile = outfile->next;
		}
	}
	return (0);
}
