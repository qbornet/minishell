#include <minishell.h> // met toujours comme ca c'est pas pour faire le relou mais vue que notre .h est dans un dossier si je make ailleur que je creer mon propre .h je vais utiliser celui qui est dans le dir ou je make donc pas de '""' 🦊

static int set_default(t_cmdblock *cmdblk)
{
	char				*str;
	struct sigaction	sa_int;
	struct sigaction	sa_new;
	struct sigaction	sa_quit;

	if (!cmdblk->cmd)
		str = "";
	else
		str = cmdblk->cmd[0];
	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_new, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_int.sa_handler = SIG_IGN;
	sa_new.sa_handler = &nint_handler;
	sa_quit.sa_handler = &nquit_handler;
	if (str && *str && !ft_strncmp(ft_last_level(str), BIN_NAME, ft_strlen(BIN_NAME)))
		sigaction(SIGINT, &sa_int, NULL);
	else
		sigaction(SIGINT, &sa_new, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	return (0);
}

static int	exec_status(t_data **frame, t_process *pr)
{
	int			wstatus;

	wstatus = 0;
	g_exit_status = 0;
	waitpid(pr->pids[0], &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_exit_status = WEXITSTATUS(wstatus);
	/* Faudrais refaire la ligne dup2 dans les pipes en gros le but ici,
	 * c'est quand j'envoie un ^C je dois close la stdin du coup,
	 * si je veux recup un prompt je suis obliger de redup juste apres.
	 * check ou tu dois le mettre dans ton code pour le refaire reprompt apres un ^C
	 * genre test cat | cat
	 * */
	dup2((*frame)->std_fd->stdin, STDIN_FILENO);
	free_pipes_pids(pr->pipes, pr->pids, 0);
	ft_unlink_tmpfiles((*frame)->cmdblk);
	return (0);
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
