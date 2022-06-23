/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:21:18 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/23 18:08:50 by jfrancai         ###   ########.fr       */
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

int	pipex_status(t_data **frame, t_process *pr)
{
	int			i;
	int			pipes_len;
	int			wstatus;
	int			status_code;

	pipes_len = pr->len_cmdb - 1;
	i = -1;
	while (++i < pipes_len)
		if (close_pipe(pr->pipes[i]) == -1)
			return (free_and_msg(pr->pipes, pr->pids, pipes_len, "pipes[i]: close error"));
	i = -1;
	while (++i < pipes_len + 1)
	{
		waitpid(pr->pids[i], &wstatus, 0);
		status_code = 0;
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
	}

	if (!pipes_len && !ft_strcmp("cd", (*frame)->cmdblk->cmd[0]))
		ft_cd((*frame)->cmdblk, (*frame)->envp);
	if (!pipes_len && !ft_strcmp("exit", (*frame)->cmdblk->cmd[0]))
		ft_exit(0);
	if (!pipes_len && !ft_strcmp("export", (*frame)->cmdblk->cmd[0]))
		ft_export((*frame)->cmdblk, &(*frame)->envp);
	if (!pipes_len && !ft_strcmp("unset", (*frame)->cmdblk->cmd[0]))
		ft_unset((*frame)->cmdblk, &(*frame)->envp);

	free_pipes_pids(pr->pipes, pr->pids, pipes_len, 0);
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
