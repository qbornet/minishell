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

int	ft_redicrection_dgreat(char *outfile)
{
	int		fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (standard_error(outfile));
	if (dup_out(fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (standard_error("pipe_out fd"));
	return (0);
}

int	set_infile(t_redirlist *infile)
{
	while (infile)
	{
		if (ft_redirection_less(infile->str) == -1)
			return (-1);
		infile = infile->next;
	}
	return (0);
}

int	set_outfile(t_redirlist *outfile)
{
	while (outfile)
	{
		if (ft_redicrection_great(outfile->str) == -1)
			return (-1);
		outfile = outfile->next;
	}
	return (0);
}

int	ft_redirection_pipe(int *pd, int pid)
{
	if (dup_out(pd[pid]) == -1)
		return (-1);
	if (close_pipe(pd) == -1)
		return (standard_error("pipe_in close pd"));
	return (0);
}

int	open_fd(int **pipes, t_cmdblock **avector, int pipes_len, int i)
{
	int			j;
	t_cmdblock	*cmdblock;

	cmdblock = *avector;
	if (i == 0)
	{
		set_infile(cmdblock->infile);
		ft_redirection_pipe(pipes[i], 1);
		set_outfile(cmdblock->outfile);
	}
	else if (i == pipes_len)
	{
		while (cmdblock->next)
			cmdblock = cmdblock->next;
		ft_redirection_pipe(pipes[i - 1], 0);
		set_infile(cmdblock->infile);
		set_outfile(cmdblock->outfile);
	}
	else
	{
		j = -1;
		while (++j != i)
			cmdblock = cmdblock->next;
		ft_redirection_pipe(pipes[i - 1], 0);
		set_infile(cmdblock->infile);
		ft_redirection_pipe(pipes[i], 1);
		set_outfile(cmdblock->outfile);
	}
	return (0);
}
