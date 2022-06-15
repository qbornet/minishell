#include "minishell.h"

t_cmdblock	*ft_next_cmdblock(int i, t_cmdblock **curr)
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

int	ft_len_cmdblock(t_cmdblock *cmdblock)
{
	int	i;

	if (!cmdblock)
		return (0);
	i = 0;
	while (cmdblock)
	{
		cmdblock = cmdblock->next;
		i++;
	}
	return (i);
}

int	ft_pipe(t_data **frame, char **envp)
{	
	int			**pipes;
	int			*pids;
	int			len_cmdb;
	int			i;

	len_cmdb = ft_len_cmdblock((*frame)->cmdblk);
	if (alloc_pipes_pids(&pipes, &pids, len_cmdb))
		return (1);
	i = -1;
	while (++i < len_cmdb)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (free_and_msg(pipes, pids, 0, "fork"));
		if (pids[i] == 0)
		{
			if (close_pipes(pipes, len_cmdb - 1, pids, i) == -1)
				return (1);
			if (open_fd(pipes, frame, len_cmdb - 1, i) == -1)
				return (free_and_return(pipes, pids, 0, 1));
			if (pipex(pipes, pids, envp, ft_next_cmdblock(i, &(*frame)->cmdblk)) == -1)
				return (errno);
		}
	}
	return (pipex_status(len_cmdb - 1, pipes, pids));
}
