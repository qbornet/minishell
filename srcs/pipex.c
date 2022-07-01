#include "minishell.h"

int	pipex(t_process *pr, t_data **frame, t_cmdblock *cmdblock)
{
	if (!cmdblock->cmd)
		return (-1);
	if (g_exit_status == 130)
		exit(g_exit_status);
	if (is_builtin(cmdblock, frame) == 0)	
		exit(0);
	if (get_cmd_tab(cmdblock, (*frame)->envp) < 0)
		return (-1);
	if (exec_cmd(cmdblock, (*frame)->envp) < 0)
		return (-1);
	exit(0);
}
