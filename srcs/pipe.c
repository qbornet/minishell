#include "minishell.h"

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
	int		**pipes;
	int		*pids;
	int		len_cmdb;
	int		i;

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
			if (close_pipes(pipes, len_cmdb, pids, i) == -1)
				return (1);
			if (open_fd(pipes, cmdblock, len_cmdb, i) == -1)
				return (free_and_return(pipes, pids, 0, 1));
			if (pipex(pipes, pids, envp, cmdblock) == -1)
				return (errno);
			cmdblock = &(*cmdblock)->next;
		}
	}
	return (pipex_status(len_cmdb, pipes, pids));
}
