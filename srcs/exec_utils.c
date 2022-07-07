/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:47:03 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 07:22:34 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_len_cmdblk(t_cmdblock *cmdblock)
{
	int	i;

	i = 0;
	while (cmdblock)
	{
		i++;
		cmdblock = cmdblock->next;
	}
	return (i);
}

static int	ft_call_heredoc(t_data **f, t_cmdblock **c, t_redirlist *fd)
{
	while (fd)
	{
		if (fd->type == E_DLESS)
		{
			if (here_doc(f, c, fd->str) < 0)
				return (-1);
			dup2((*f)->std_fd->stdin, 0);
			ioctl(STDIN_FILENO, TIOCSCTTY, 0);
		}
		fd = fd->next;
	}
	return (0);
}

int	ft_init_exec(t_data **frame)
{
	int			len;
	t_cmdblock	*cmdblock;

	cmdblock = (*frame)->cmdblk;
	len = ft_len_cmdblk(cmdblock);
	while (cmdblock)
	{
		if (ft_call_heredoc(frame, &cmdblock, cmdblock->fd) < 0)
			return (-1);
		cmdblock->len = len;
		cmdblock = cmdblock->next;
	}
	return (len);
}

int	get_cmd_tab(t_cmdblock *cmdblock, char **env)
{
	char	*path;
	char	**cmd;

	cmd = cmdblock->cmd;
	if (*cmd && !**cmd)
		return (ft_perror_ret(cmd[0], E_NOT_FOUND, -1));
	path = get_path(env, cmd[0]);
	if (!path)
		return (-1);
	free(cmd[0]);
	cmd[0] = path;
	if (access((cmdblock->cmd)[0], X_OK) == -1)
		return (ft_perror_ret((cmdblock->cmd)[0], E_DENIED, -1));
	cmdblock->cmd = cmd;
	return (0);
}

int	exec(t_data **frame, t_cmdblock *cmdblock)
{
	if (!cmdblock->cmd)
		return (-1);
	if (g_exit_status == 130 || g_exit_status == 131)
		exit(g_exit_status);
	if (get_cmd_tab(cmdblock, (*frame)->envp) < 0)
		exit(g_exit_status);
	if (execve((cmdblock->cmd)[0], cmdblock->cmd, (*frame)->envp) < 0)
		exit(g_exit_status);
	exit(0);
}
