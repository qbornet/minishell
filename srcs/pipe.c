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

static int	pipex(t_data **frame, t_cmdblock *cmdblock)
{
	int	code;

	code = is_builtin(cmdblock, frame);
	if (code == 0)
		exit(0);
	if (code < 0)
		return (-1);
	if (exec(frame, cmdblock) < 0)
		return (-1);
	exit(0);
}

int	ft_pipe(t_process *pr, t_data **frame)
{	
	int			i;

	i = -1;
	while (++i < pr->len_cmdb)
	{
		pr->pids[i] = fork();
		if (pr->pids[i] == -1)
			return (free_and_msg(pr->pipes
					, pr->pids, "fork"));
		if (pr->pids[i] == 0)
		{
			if (close_pipes(pr, i) == -1)
				return (-1);
			if (open_fd(pr, (*frame)->cmdblk, i) == -1)
				return (-1);
			if (pipex(frame, next_cmdb(i, &(*frame)->cmdblk)) == -1)
				return (-1);
		}
	}
	return (pipex_status(frame, pr));
}
