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

static int	ft_len_cmdblk(t_cmdblock *cmdblock)
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

static int	ft_init_exec(t_data **frame)
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

int	ft_pipe(t_data **frame)
{	
	int			i;

	(*frame)->pr.len_cmdb = ft_init_exec(frame);
	if (alloc_pipes_pids(&(*frame)->pr))
		return (-1);
	i = -1;
	while (++i < (*frame)->pr.len_cmdb)
	{
		(*frame)->pr.pids[i] = fork();
		if ((*frame)->pr.pids[i] == -1)
			return (free_and_msg((*frame)->pr.pipes, (*frame)->pr.pids, (*frame)->pr.len_cmdb - 1, "fork"));
		if ((*frame)->pr.pids[i] == 0)
		{
			if (close_pipes((*frame)->pr.pipes, (*frame)->pr.len_cmdb - 1, (*frame)->pr.pids, i) == -1)
				return (-1);
			if (open_fd((*frame)->pr.pipes, frame, (*frame)->pr.len_cmdb - 1, i) == -1)
				return (free_pipes_pids((*frame)->pr.pipes, (*frame)->pr.pids, (*frame)->pr.len_cmdb - 1, -1));
			if (pipex((*frame)->pr.pipes, (*frame)->pr.pids, (*frame)->envp, next_cmdb(i, &(*frame)->cmdblk)) == -1)
				return (-1);
		}
	}
	return (pipex_status(frame, (*frame)->pr.len_cmdb - 1, (*frame)->pr.pipes, (*frame)->pr.pids));
}
