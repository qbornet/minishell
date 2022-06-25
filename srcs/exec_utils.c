/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:42 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:52:21 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	ft_call_heredoc(t_data **f, t_cmdblock **c, t_redirlist *infile)
{
	while (infile)
	{
		if (infile->type == E_DLESS)
		{
			if (here_doc(f, c, infile->str) < 0)
				return (-1);
			dup2((*f)->std_fd->stdin, 0);
			ioctl(STDIN_FILENO, TIOCSCTTY, 0);
		}
		infile = infile->next;
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
		if (ft_call_heredoc(frame, &cmdblock, cmdblock->infile) < 0)
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
	if (!*cmd)
		return (-1);
	path = get_path(env, cmd[0]);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (-1);
	}
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
