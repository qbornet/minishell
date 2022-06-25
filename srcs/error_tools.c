/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:35 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:50:51 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unlink_tmpfiles(t_cmdblock *cmdblock)
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

int	pipex_status(t_data **frame, t_process *pr)
{
	int			i;
	int			pipes_len;
	int			wstatus;

	pipes_len = pr->len_cmdb - 1;
	i = -1;
	while (++i < pipes_len)
		if (close_pipe(pr->pipes[i]) == -1)
			return (free_and_msg(pr->pipes,
					pr->pids, pipes_len, "pipes[i]: close error"));
	i = -1;
	while (++i < pipes_len + 1)
	{
		waitpid(pr->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_exit_status = WEXITSTATUS(wstatus);
	}
	free_pipes_pids(pr->pipes, pr->pids, pipes_len, 0);
	ft_unlink_tmpfiles((*frame)->cmdblk);
	return (g_exit_status);
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
