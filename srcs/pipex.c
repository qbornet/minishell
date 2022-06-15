/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:31:57 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/15 17:26:41 by qbornet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_tab(t_cmdblock *cmdblock, char **env)
{
	char	*path;
	char	**cmd;

	cmd = cmdblock->cmd;
	if (!*cmd)
		return (-1);
	path = get_path(env, cmd[0]);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_str_tab(cmd, 0);
		return (-1);
	}
	free_str(cmd[0]);
	cmd[0] = path;
	cmdblock->cmd = cmd;
	return (0);
}

int	exec_cmd(t_cmdblock *cmdblock, char **env)
{
	if (access((cmdblock->cmd)[0], X_OK) == -1)
	{
		perror((cmdblock->cmd)[0]);
		free_str_tab(cmdblock->cmd, 0);
		exit(127);
	}
	execve((cmdblock->cmd)[0], cmdblock->cmd, env);
	exit(0);
}

int	pipex(int **pipes, int *pids, char **envp, t_cmdblock *cmdblock)
{
	if (get_cmd_tab(cmdblock, envp) == -1)
	{
		errno = free_and_return(pipes, pids, 0, 127);
		return (-1);
	}
	if (exec_cmd(cmdblock, envp) == -1)
	{
		errno = free_and_return(pipes, pids, 0, 126);
		return (-1);
	}
	exit(0);
}
