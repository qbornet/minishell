#include <minishell.h>

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
		start_prompt();
}

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
		return ;
}

int	term_isig(const struct termios *term)
{
	if (term->c_lflag & ISIG)
		return (1);
	return (0);
}

int	set_sig(struct sigaction *act_int, struct sigaction *act_quit)
{
	ft_memset(act_int, 0, sizeof(struct sigaction));
	ft_memset(act_quit, 0, sizeof(struct sigaction));
	if (sigemptyset(act_int->sa_mask) < 0)
		return (-1);
	if (sigemptyset(act_quit->sa_mask) < 0)
		return (-1);
	if (sigaddset(act_int->sa_mask, SIGINT) < 0)
		return (-1);
	if (sigaddset(act_quit->sa_mask, SIGQUIT) < 0)
		return (-1);
	act_int->sa_handler = &sigint_handler;
	act_quit->sa_handler = &sigquit_handler;
	if (sigaction(SIGINT, act_int, NULL) < 0)
		return (-1);
	if (sigaction(SIGQUIT, act_quit, NULL) < 0)
		return (-1);
	return (0);
}
