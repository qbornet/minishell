#include <minishell.h>

static void	opt_default(struct sigaction *sa_int, struct sigaction *sa_new, struct sigaction *sa_quit)
{
	ft_memset(sa_int, 0, sizeof(struct sigaction));
	ft_memset(sa_new, 0, sizeof(struct sigaction));
	ft_memset(sa_quit, 0, sizeof(struct sigaction));
	sa_int->sa_handler = SIG_IGN;
	sa_new->sa_handler = &nint_handler;
	sa_quit->sa_handler = &nquit_handler;
}

static int set_default(t_cmdblock *cmdblk)
{
	char				*str;
	struct sigaction	sa_int;
	struct sigaction	sa_new;
	struct sigaction	sa_quit;

	str = "";
	if (cmdblk->cmd[0])
		str = cmdblk->cmd[0];
	opt_default(&sa_int, &sa_new, &sa_quit);
	if (str && *str && !ft_strncmp(ft_last_level(str), BIN_NAME, ft_strlen(BIN_NAME)))
	{
		if (sigaction(SIGINT, &sa_int, NULL) < 0)
			return (-1);
	}
	else
	{
		if (sigaction(SIGINT, &sa_new, NULL) < 0)
			return (-1);
	}
	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		return (-1);
	return (0);
}

int	exec_status(t_data **frame, t_process *pr)
{
	int			i;
	int			pipes_len;
	int			wstatus;
	t_cmdblock	*cmdblk;

	i = -1;
	pipes_len = pr->len_cmdb - 1;
	cmdblk = (*frame)->cmdblk;
	while (++i < pipes_len)
	{
		if (close_pipe(pr->pipes[i]) == -1)
		{
			dup2((*frame)->std_fd->stdin, STDIN_FILENO);
			dup2((*frame)->std_fd->stdout, STDIN_FILENO);
			ft_unlink_tmpfiles((*frame)->cmdblk);
			return (free_and_msg(pr->pipes,
				pr->pids, "pipes[i]: close error"));
		}
	}
	i = -1;
	while (++i < pipes_len + 1)
	{
		waitpid(pr->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_exit_status = WEXITSTATUS(wstatus);
		if (underscore(cmdblk, frame) < 0)
			return (-1);
		cmdblk = cmdblk->next;
	}
	dup2((*frame)->std_fd->stdin, STDIN_FILENO);
	dup2((*frame)->std_fd->stdout, STDIN_FILENO);
	ft_unlink_tmpfiles((*frame)->cmdblk);
	free_pipes_pids(pr->pipes, pr->pids, 0);
	return (g_exit_status);
}

static int	exec_single(t_process *pr, t_data **frame)
{
	pr->pids[0] = fork();
	if (pr->pids[0] == -1)
		return (free_and_msg(pr->pipes, pr->pids, "fork"));
	if (pr->pids[0] == 0)
	{
		if (open_fd(pr, (*frame)->cmdblk, 0) == -1)
			return (-1);
		if (exec(frame, (*frame)->cmdblk) == -1)
			return (-1);
	}
	return (exec_status(frame, pr));
}

int	run_exec(t_data **frame)
{
	int			code;
	t_process	*pr;

	pr = &(*frame)->pr;
	if (set_default((*frame)->cmdblk) < 0)
		return (-1);
	pr->len_cmdb = ft_init_exec(frame);
	if (pr->len_cmdb - 1 == 0)
	{
		code = exec_builtin_single((*frame)->cmdblk, frame);
		if (!code || code < 0)
			return (0);
	}
	if (alloc_pipes_pids(pr))
		return (-1);
	if (pr->len_cmdb - 1)
		return (ft_pipe(pr, frame));
	return (exec_single(pr, frame));
}
