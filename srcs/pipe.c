#include "minishell.h"

static t_cmdblock	*ft_next_cmdblock(int i, t_cmdblock **curr)
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

int	ft_pipe(t_cmdblock **cmdblock, char **envp)
{	
	int			**pipes;
	int			*pids;
	int			len_cmdb;
	int			i;
	t_cmdblock	*usage;

	len_cmdb = ft_len_cmdblock(*cmdblock);
	if (alloc_pipes_pids(&pipes, &pids, len_cmdb))
		return (1);
	i = -1;
	while (++i < len_cmdb + 1)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (free_and_msg(pipes, pids, 0, "fork"));
		if (pids[i] == 0)
		{
			usage = ft_next_cmdblock(i, cmdblock);
			if (close_pipes(pipes, len_cmdb, pids, i) == -1)
				return (1);
			if (open_fd(pipes, cmdblock, len_cmdb, i) == -1)
				return (free_and_return(pipes, pids, 0, 1));
			if (pipex(pipes, pids, envp, usage) == -1)
				return (errno);
		}
	}
	return (pipex_status(len_cmdb, pipes, pids));
}
