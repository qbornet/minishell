/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:50 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 14:00:52 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	dup_stdinout(t_termstd *std_fd)
{
	if (dup2(std_fd->stdin, STDIN_FILENO) < 0)
		return (-1);
	if (dup2(std_fd->stdout, STDIN_FILENO) < 0)
		return (-1);
	return (0);
}

int	dup_in(int new_in)
{
	if (dup2(new_in, STDIN_FILENO) == -1)
		return (-1);
	return (0);
}

int	dup_out(int new_out)
{
	if (dup2(new_out, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

int	close_pipe(int *pd)
{
	if (close(pd[0]) == -1)
		return (-1);
	if (close(pd[1]) == -1)
		return (-1);
	return (0);
}

int	set_fd(t_redirlist *fd)
{
	while (fd)
	{
		if (fd->type == E_GREAT)
			if (ft_redirection_great(fd->str) == -1)
				return (-1);
		if (fd->type == E_DGREAT)
			if (ft_redirection_dgreat(fd->str) == -1)
				return (-1);
		if (fd->type == E_LESS || fd->type == E_DLESS)
			if (ft_redirection_less(fd->str) == -1)
				return (-1);
		fd = fd->next;
	}
	return (0);
}
