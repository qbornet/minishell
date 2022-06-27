/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:59:15 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/27 13:59:32 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		status;

	(void)ac;
	(void)av;
	pid = fork();
	if (pid == 0)
	{
		execve("/bin/clear", ((char *[]){"clear", NULL}), envp);
		return (0);
	}
	else if (pid == -1)
		return (0);
	else
	{
		waitpid(pid, &status, 0);
		start(envp);
	}
	return (0);
}
