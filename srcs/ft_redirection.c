/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:28:40 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:28:41 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	ft_redirection_great(char *outfile)
{
	int		fd;

	unlink(outfile);
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (standard_error(outfile));
	if (dup_out(fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (standard_error("pipe_out fd"));
	return (0);
}

int	ft_redirection_dgreat(char *outfile)
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

int	ft_redirection_pipe_out(int *pd, int pid)
{
	if (dup_out(pd[pid]) == -1)
		return (-1);
	if (close_pipe(pd) == -1)
		return (standard_error("pipe_out close pd"));
	return (0);
}

int	ft_redirection_pipe_in(int *pd, int pid)
{
	if (dup_in(pd[pid]) == -1)
		return (-1);
	if (close_pipe(pd) == -1)
		return (standard_error("pipe_in close pd"));
	return (0);
}
