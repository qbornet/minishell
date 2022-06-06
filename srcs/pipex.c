/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:31:57 by jfrancai          #+#    #+#             */
/*   Updated: 2022/03/01 11:12:44 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_cmd_tab(char *cmd_string, char **env, char ***cmd)
{
	char	*path;

	*cmd = ft_split(cmd_string, ' ');
	if (!*cmd)
		return (-1);
	path = get_path(env, (*cmd)[0]);
	if (!path)
	{
		ft_putstr_fd(cmd_string, 2);
		ft_putendl_fd(": command not found", 2);
		free_str_tab(*cmd, 0);
		return (-1);
	}
	free_str((*cmd)[0]);
	(*cmd)[0] = path;
	return (0);
}

int	exec_cmd(char **cmd, char **env)
{
	if (access(cmd[0], X_OK) == -1)
	{
		perror(cmd[0]);
		free_str_tab(cmd, 0);
		return (-1);
	}
	execve(cmd[0], cmd, env);
	return (0);
}

int	pipex(int **pipes, int *pids, char **envp, char *raw_cmd)
{
	char	**cmd_tab;

	cmd_tab = NULL;
	if (get_cmd_tab(raw_cmd, envp, &cmd_tab) == -1)
	{
		errno = free_and_return(pipes, pids, 0, 127);
		return (-1);
	}
	if (exec_cmd(cmd_tab, envp) == -1)
	{
		errno = free_and_return(pipes, pids, 0, 126);
		return (-1);
	}
	return (0);
}
