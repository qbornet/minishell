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

static int	ret_perror(char *str)
{
	perror(str);
	return (-1);
}

static int	set_start(struct termios *t, struct sigaction *act_int, struct sigaction *act_quit)
{
	if (ft_check_tty())
	{
		if (set_sig(act_int, act_quit) < 0)
			return (ret_perror("sigaction(), sigemptyset(), sigaddset() "));
		if (tcgetattr(STDIN_FILENO, t) < 0)
			return (ret_perror("tcgetattr() "));
		if (t->c_lflag & ECHOCTL)
			t->c_lflag &= ~ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, t) < 0)
			return (ret_perror("tsetattr() "));
	}
	else
		return (-1);
	return (0);
}

int	start_prompt(t_data **d_curr)
{
	char				*str;
	struct termios		term;
	struct sigaction	act_int;
	struct sigaction	act_quit;

	str = "";
	if (set_start(&term, &act_int, &act_quit) < 0)
		return (exit_group(d_curr));
	while (str && ft_check_tty() && term_isig(&term))
	{
		str = readline(PROMPT);
		ft_history(str);
		if (lexer_parser_main(str, (*d_curr)->envp, d_curr) < 0)
			return (exit_group(d_curr));
		if (start_expansion(d_curr) < 0)
			return (exit_group(d_curr));
		if (ft_pipe(&(*d_curr)->cmdblk, (*d_curr)->envp) < 0)
			return (exit_group(d_curr));
		free_redoo(d_curr, str);
	}
	return (write(1, "exit\n", 5) && exit_group(d_curr));
}
