#include <minishell.h>

int		g_exit_status;

int	ft_error_here(char *word)
{
	free(word);
	return (-1);
}

char	*ft_error_ret(char *str)
{
	free(str);
	return (NULL);
}

char	*ft_error_malloc(char **arr)
{
	size_t	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	return (NULL);
}

void	heredoc_handler(int signum)
{
	struct sigaction	act;

	if (signum == SIGINT)
	{
		ft_memset(&act, 0, sizeof(struct sigaction));
		close(0);
		write(1, "^C", 2);
		sigaddset(&act.sa_mask, SIGINT);
		act.sa_handler = &sigint_handler;
		sigaction(SIGINT, &act, NULL);
		g_exit_status = 130;
	}
}
