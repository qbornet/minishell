#include <minishell.h>

static void	ft_history(char *str)
{
	if (str && *str)
		add_history(str);
}


static int	ft_check_tty(void)
{
	if (isatty(STDIN_FILENO) &&
		isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		return (1);
	return (0);
}

static int	set_start(struct termios *t, struct sigaction *act_int, struct sigaction *act_quit)
{

	if (!ft_check_tty())
	{
		ioctl(STDIN_FILENO, TIOCSCTTY, 0);
		ioctl(STDOUT_FILENO, TIOCSCTTY, 0);
		ioctl(STDERR_FILENO, TIOCSCTTY, 0);
	}
	if (ft_check_tty())
	{
		if (set_sig(act_int, act_quit) < 0)
			return (-1);
		if (tcgetattr(STDIN_FILENO, t) < 0)
			return (-1);
		if (t->c_lflag & ECHOCTL)
			t->c_lflag &= ~ECHOCTL;
		if (t->c_lflag & TOSTOP)
			t->c_lflag &= ~TOSTOP;
		if (tcsetattr(STDIN_FILENO, TCSANOW, t) < 0)
			return (-1);
	}
	return (0);
}

int	start_prompt(t_data **d_curr)
{
	char				*str;
	int					code;
	struct termios		term;
	struct sigaction	act_int;
	struct sigaction	act_quit;

	str = "";
	ft_addlevel(&(*d_curr)->envp);
	g_exit_status = 0;
	while (str && ft_check_tty())
	{
		if (set_start(&term, &act_int, &act_quit) < 0)
			return (exit_group(d_curr));
		str = readline(PROMPT);
		if (!str)
			return (write(1, "exit\n", 5) && exit_group(d_curr));
		ft_history(str);
		code = lexer_parser_main(str, (*d_curr)->envp, d_curr);
		if (code < 0)
			return (exit_group(d_curr));
		if (!code)
		{
			if (start_expansion(d_curr) < 0)
				return (exit_group(d_curr));
			if (g_exit_status == 130 || g_exit_status == 131)
				g_exit_status = 0;
			if (run_exec(d_curr) < 0)
				return (exit_group(d_curr));
		}
		free_redoo(d_curr, str);
	}
	return (write(1, "exit\n", 5) && exit_group(d_curr));
}
