#include "minishell.h"

static int	pipex_builtin(t_process *pr, t_data **frame, t_cmdblock *cmdblock)
{
	int	exec_code;

	exec_code = is_builtin(cmdblock, frame);
	if (exec_code == 0)
		exit(0);
	else if (exec_code < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 126;
		return (-1);
	}
	return (exec_code);
}

int	pipex(t_process *pr, t_data **frame, t_cmdblock *cmdblock)
{
	if (!cmdblock->cmd)
		return (-1);
	if (g_exit_status == 130)
		exit(g_exit_status);
	if (pipex_builtin(pr, frame, cmdblock) < 0)	
		return (-1);
	if (get_cmd_tab(cmdblock, (*frame)->envp) < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 127;
		if (cmdblock->cmd)
			ft_perror(cmdblock->cmd[0], 0);
		return (-1);
	}
	if (exec_cmd(cmdblock, (*frame)->envp) < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 126;
		if (cmdblock->cmd)
			ft_perror(cmdblock->cmd[0], 0);
		return (-1);
	}
	exit(0);
}
