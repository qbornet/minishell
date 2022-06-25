/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:32 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:29:33 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
