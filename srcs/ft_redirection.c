/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:28:40 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 14:00:06 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_redirection_less(char *infile)
{
	int		fd;

	ft_removes_quotes(&infile);
	if (!access(infile, F_OK) && (access(infile, F_OK) < 0
			|| access(infile, R_OK) < 0))
		return (ft_perror_ret(infile, E_DENIED_1, -1));
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		return (ft_perror_ret(infile, E_NOT_EXIST, -1));
	if (dup_in(fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	ft_redirection_great(char *outfile)
{
	int			fd;

	ft_removes_quotes(&outfile);
	if (!is_file(outfile) && is_dir(outfile))
		return (ft_perror_ret(outfile, E_IS_DIR_1, -1));
	if (!access(outfile, F_OK) && (access(outfile, F_OK) < 0
			|| access(outfile, W_OK) < 0))
		return (ft_perror_ret(outfile, E_DENIED_1, -1));
	unlink(outfile);
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (ft_perror_ret(outfile, E_NOT_EXIST, -1));
	if (dup_out(fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	ft_redirection_dgreat(char *outfile)
{
	int		fd;

	ft_removes_quotes(&outfile);
	if (!is_file(outfile) && is_dir(outfile))
		return (ft_perror_ret(outfile, E_IS_DIR_1, -1));
	if (!access(outfile, F_OK) && (access(outfile, F_OK) < 0
			|| access(outfile, W_OK) < 0))
		return (ft_perror_ret(outfile, E_DENIED_1, -1));
	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		return (ft_perror_ret(outfile, E_NOT_EXIST, -1));
	if (dup_out(fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	ft_redirection_pipe_out(int *pd, int pid)
{
	if (dup_out(pd[pid]) == -1)
		return (-1);
	if (close_pipe(pd) == -1)
		return (-1);
	return (0);
}

int	ft_redirection_pipe_in(int *pd, int pid)
{
	if (dup_in(pd[pid]) == -1)
		return (-1);
	if (close_pipe(pd) == -1)
		return (-1);
	return (0);
}
