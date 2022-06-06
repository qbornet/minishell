/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:19:55 by jfrancai          #+#    #+#             */
/*   Updated: 2022/03/01 11:12:22 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipe_in(char *infile, int *pd)
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

int	pipe_mid(int *pd_in, int *pd_out)
{
	if (dup_inout(pd_in[0], pd_out[1]) == -1)
		return (standard_error("pipe_mid dup_inout"));
	if (close_pipe(pd_in) == -1)
		return (standard_error("pipe_mid close pd_in"));
	if (close_pipe(pd_out) == -1)
		return (standard_error("pipe_mid close pd_out"));
	return (0);
}

int	pipe_out(int *pd, char *outfile)
{
	int		fd;

	if (unlink(outfile) == -1)
		errno = 0;
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
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

int	open_fd(int **pipes, char **avector, int pipes_len, int i)
{
	if (i == 0)
	{
		if (pipe_in(avector[1], pipes[i]) == -1)
			return (-1);
	}
	else if (i == pipes_len)
	{
		if (pipe_out(pipes[i - 1], avector[pipes_len + 3]) == -1)
			return (-1);
	}
	else
	{
		if (pipe_mid(pipes[i - 1], pipes[i]) == -1)
			return (-1);
	}
	return (0);
}
