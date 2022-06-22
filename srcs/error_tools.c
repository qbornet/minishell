/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:21:18 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/22 14:23:54 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unlink_tmpfiles(t_cmdblock *cmdblock)
{
	t_redirlist	*infile;

	while (cmdblock)
	{
		infile = cmdblock->infile;
		while (infile)
		{
			if (infile->type == E_DLESS)
				unlink(infile->str);
			infile = infile->next;
		}
		cmdblock = cmdblock->next;
	}
	return (0);
}

int	pipex_status(t_data **frame, int pipes_len, int **pipes, int *pids)
{
	int			i;
	int			wstatus;
	int			status_code;

	i = -1;
	while (++i < pipes_len)
		if (close_pipe(pipes[i]) == -1)
			return (free_and_msg(pipes, pids, pipes_len, "pipes[i]: close error"));
	i = -1;
	while (++i < pipes_len + 1)
	{
		waitpid(pids[i], &wstatus, 0);
		status_code = 0;
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
	}
	free_pipes_pids(pipes, pids, pipes_len, 0);
	ft_unlink_tmpfiles((*frame)->cmdblk);
	return (status_code);
}

int	standard_error(char *str)
{
	perror(str);
	return (-1);
}

int	main_error(char *str)
{
	perror(str);
	return (1);
}

int	error(char *str)
{
	if (errno)
		return (main_error(str));
	else
		return (ft_putendl_fd(str, 2));
	return (2);
}
