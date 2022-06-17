#include "minishell.h"

t_cmdblock	*next_cmdb(int i, t_cmdblock **curr)
{
	t_cmdblock	*cmdblk;

	cmdblk = *curr;
	while (i && cmdblk->next)
	{
		cmdblk = cmdblk->next;
		i--;
	}
	return (cmdblk);
}
static int	ft_call_heredoc(t_data **frame, t_cmdblock **cmdblock, t_redirlist *infile)
{
	while (infile)
	{
		if (infile->type == E_DLESS)
		{
			if (here_doc(frame, cmdblock, infile->str) < 0)
				return (-1);
			dup2((*frame)->std_fd->stdin, 0);
			ioctl(STDIN_FILENO, TIOCSCTTY, 0);
		}
		infile = infile->next;
	}
	return (0);
}

static int	ft_init_exec(t_data **frame)
{
	int			i;
	t_cmdblock	*cmdblock;

	cmdblock = (*frame)->cmdblk;
	if (!cmdblock)
		return (0);
	i = 0;
	while (cmdblock)
	{
		i++;
		cmdblock = cmdblock->next;
	}
	cmdblock = (*frame)->cmdblk;
	while (cmdblock)
	{
		if (ft_call_heredoc(frame, &cmdblock, cmdblock->infile) < 0)
			return (-1);
		cmdblock->len = i;
		cmdblock = cmdblock->next;
	}
	return (i);
}

int	ft_pipe(t_data **frame, char **envp)
{	
	int			**pipes;
	int			*pids;
	int			len_cmdb;
	int			i;

	len_cmdb = ft_init_exec(frame);
	if (alloc_pipes_pids(&pipes, &pids, len_cmdb))
		return (-1);
	i = -1;
	while (++i < len_cmdb)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (free_and_msg(pipes, pids, len_cmdb - 1, "fork"));
		if (pids[i] == 0)
		{
			if (close_pipes(pipes, len_cmdb - 1, pids, i) == -1)
				return (-1);
			if (open_fd(pipes, frame, len_cmdb - 1, i) == -1)
				return (free_pipes_pids(pipes, pids, len_cmdb - 1, -1));
			if (pipex(pipes, pids, envp, next_cmdb(i, &(*frame)->cmdblk)) == -1)
				return (-1);
		}
	}
	return (pipex_status(len_cmdb - 1, pipes, pids));
}
