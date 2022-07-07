/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:52 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:29:52 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_first(int **pipes, t_cmdblock *cmdblock, int i)
{
	if (ft_redirection_pipe_out(pipes[i], 1) < 0)
		return (-1);
	if (set_fd(cmdblock->fd) < 0)
		return (-1);
	return (0);
}

static int	open_last(int **pipes, t_cmdblock *cmdblock, int i)
{
	while (cmdblock->next)
		cmdblock = cmdblock->next;
	if (ft_redirection_pipe_in(pipes[i - 1], 0) < 0)
		return (-1);
	if (set_fd(cmdblock->fd) < 0)
		return (-1);
	return (0);
}

static int	open_mid(int **pipes, t_cmdblock *cmdblock, int i)
{
	cmdblock = next_cmdb(i, &cmdblock);
	if (ft_redirection_pipe_in(pipes[i - 1], 0) < 0)
		return (-1);
	if (ft_redirection_pipe_out(pipes[i], 1) < 0)
		return (-1);
	if (set_fd(cmdblock->fd) < 0)
		return (-1);
	return (0);
}

int	open_fd(t_process *pr, t_cmdblock *cmdblock, int i)
{
	int	pipes_len;

	pipes_len = pr->len_cmdb - 1;
	if (pipes_len == 0)
	{
		if (set_fd(cmdblock->fd) < 0)
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
