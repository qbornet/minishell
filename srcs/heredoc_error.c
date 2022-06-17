#include <minishell.h>

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
	if (signum == SIGINT)
	{
		rl_replace_line(NULL, 0);
		rl_redisplay();
		exit(0);
	}
}
