#include <minishell.h>

void	ft_history(char *str)
{
	if (str && *str)
		add_history(str);
}

int	ret_perror(char *str)
{
	perror(str);
	return (-1);
}

int	ft_check_tty(void)
{
	if (isatty(STDIN_FILENO) &&
		isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		return (1);
	return (0);
}

int	start_prompt(void)
{
	char				*str;
	struct termios		term;
	struct sigaction	act_int;
	struct sigaction	act_quit;

	str = "";
	if (set_sig(&act_int, &act_quit) < 0)
		return (ret_perror("sigaction, sigemptyset, sigaddset: Error "));
	if (tcgetattr(STDIN_FILENO, &term) < 0)
		return (ret_perror("termios tcgetattr: Error "));
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		return (ret_perror("termios tcsetattr: Error "));
	while (str)
	{
		if (ft_check_tty() && term_isig(&term))
		{
			str = readline(PROMPT);
			ft_history(str);
		}
		else
			return (perror("tty: Error"));
	}
	return (0);
}

/*
int	main(void)
{
	start_prompt();
	return (0);
}
*/
