#include "minishell.h"

int	pipex(t_process *pr, t_data **frame, t_cmdblock *cmdblock)
{
	int	code;

	if (!cmdblock->cmd)
		return (-1);
	if (g_exit_status == 130)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		exit(g_exit_status);
	}
	code = is_builtin(cmdblock, frame);
	if (code == 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		exit(0);
	}
	if (code < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		return (-1);
	}
	if (get_cmd_tab(cmdblock, (*frame)->envp) < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		return (-1);
	}
	if (exec_cmd(cmdblock, (*frame)->envp) < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		return (-1);
	}
	exit(0);
}
