#include "minishell.h"


int	pipex(t_process *pr, t_data **frame, t_cmdblock *cmdblock)
{
	int	exec_code;

	if (g_exit_status == 130)
		exit(g_exit_status);
	exec_code = exec_builtin(cmdblock, frame);
	if (exec_code == 0)
		exit(0);
	else if (exec_code < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 126;
		return (-1);
	}
	if (get_cmd_tab(cmdblock, (*frame)->envp) < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 127;
		return (-1);
	}
	if (exec_cmd(cmdblock, (*frame)->envp) < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 126;
		return (-1);
	}
	exit(0);
}
