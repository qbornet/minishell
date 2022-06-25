/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:40 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:27:41 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmdblock *cmdblock, t_data **frame)
{
	if (!cmdblock->cmd || !cmdblock->cmd[0])
		return (0);
	if (!ft_strcmp("echo", cmdblock->cmd[0]))
		return (ft_echo(cmdblock));
	if (!ft_strcmp("cd", cmdblock->cmd[0]))
		return (ft_cd((*frame)->cmdblk, (*frame)->envp));
	if (!ft_strcmp("pwd", cmdblock->cmd[0]))
		return (ft_pwd());
	if (!ft_strcmp("export", cmdblock->cmd[0]))
		return (ft_export(frame));
	if (!ft_strcmp("unset", cmdblock->cmd[0]))
		return (ft_unset(frame));
	if (!ft_strcmp("env", cmdblock->cmd[0]))
		return (ft_env((*frame)->envp));
	if (!ft_strcmp("exit", cmdblock->cmd[0]))
		ft_exit(frame, 0);
	return (1);
}

int	exec_builtin_single(t_cmdblock *cmdblock, t_data **frame)
{
	int			exec_code;
	t_process	*pr;

	pr = &(*frame)->pr;
	if (open_fd(pr, cmdblock, 0) == -1)
		return (-1);
	exec_code = is_builtin(cmdblock, frame);
	if (dup_out((*frame)->std_fd->stdout) == -1)
		return (-1);
	if (dup_in((*frame)->std_fd->stdin) == -1)
		return (-1);
	if (exec_code < 0)
	{
		g_exit_status = 126;
		return (-1);
	}
	return (exec_code);
}
