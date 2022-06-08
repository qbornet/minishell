/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:44:07 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/08 21:43:05 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	main(int argc, char **argv, char **envp)
{	
	int		**pipes;
	int		*pids;
	int		i;

	if (argc < 5)
		return (ft_putendl_fd("argc: bag arguments", 2));
	if (alloc_pipes_pids(&pipes, &pids, argc - 4))
		return (1);
	i = -1;
	while (++i < argc - 4 + 1)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (free_and_msg(pipes, pids, 0, "fork"));
		if (pids[i] == 0)
		{
			if (close_pipes(pipes, argc - 4, pids, i) == -1)
				return (1);
			if (open_fd(pipes, argv, argc - 4, i) == -1)
				return (free_and_return(pipes, pids, 0, 1));
			if (pipex(pipes, pids, envp, argv[i + 2]) == -1)
				return (errno);
		}
	}
	return (pipex_status(argc - 4, pipes, pids));
}
*/
