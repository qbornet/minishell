#include "minishell.h"

static int	exec_status(t_data **frame, t_process *pr)
{
	int			wstatus;
	int			status_code;

	waitpid(pr->pids[0], &wstatus, 0);
	status_code = 0;
	if (WIFEXITED(wstatus))
		status_code = WEXITSTATUS(wstatus);
	free_pipes_pids(pr->pipes, pr->pids, 0, 0);
	ft_unlink_tmpfiles((*frame)->cmdblk);
	return (status_code);
}

static int	exec(t_process *pr, t_data **frame, t_cmdblock *cmdblock)
{
	if (g_exit_status == 130)
		exit(g_exit_status);
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

static int	exec_single(t_process *pr, t_data **frame)
{
	pr->pids[0] = fork();
	if (pr->pids[0] == -1)
		return (free_and_msg(pr->pipes, pr->pids, pr->len_cmdb - 1, "fork"));
	if (pr->pids[0] == 0)
	{
		if (open_fd(pr, (*frame)->cmdblk, 0) == -1)
			return (free_pipes_pids(pr->pipes, pr->pids, pr->len_cmdb - 1, -1));
		if (exec(pr, frame, (*frame)->cmdblk) == -1)
			return (-1);
	}
	return (exec_status(frame, pr));
}

int	run_exec(t_data **frame)
{
	int			exec_code;
	t_process	*pr;

	pr = &(*frame)->pr;
	pr->len_cmdb = ft_init_exec(frame);
	if (pr->len_cmdb - 1 == 0)
	{
		exec_code = exec_builtin_single((*frame)->cmdblk, frame);
		if (!exec_code || exec_code < 0)
			return (0);
	}
	if (alloc_pipes_pids(pr))
		return (-1);
	if (pr->len_cmdb - 1)
		return (ft_pipe(pr, frame));
	return (exec_single(pr, frame));
}
