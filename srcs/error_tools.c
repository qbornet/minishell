/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:21:18 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/08 21:45:22 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_status(int pipes_len, int **pipes, int *pids)
{
	int	wstatus;
	int	status_code;
	int	i;

	i = -1;
	while (++i < pipes_len)
		if (close_pipe(pipes[i]) == -1)
			return (free_and_msg(pipes, pids, 0, "pipes[i]: close error"));
	i = -1;
	while (++i < pipes_len + 1)
	{
		waitpid(pids[i], &wstatus, 0);
		status_code = 0;
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
	}
	free_and_return(pipes, pids, 0, 1);
	return (status_code);
}

int	standard_error(char *str)
{
	perror(str);
	return (-1);
}

int	main_error(char *str)
{
	perror(str);
	return (1);
}

int	error(char *str)
{
	if (errno)
		return (main_error(str));
	else
		return (ft_putendl_fd(str, 2));
	return (2);
}
