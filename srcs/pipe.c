/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:50 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:29:50 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdblock	*next_cmdb(int i, t_cmdblock **curr)
{
	t_cmdblock	*cmdblk;

	cmdblk = *curr;
	while (i && cmdblk->next)
	{
		cmdblk = cmdblk->next;
		i--;
	}
	return (cmdblk);
}

int	ft_pipe(t_process *pr, t_data **frame)
{	
	int			i;

	i = -1;
	while (++i < pr->len_cmdb)
	{
		pr->pids[i] = fork();
		if (pr->pids[i] == -1)
			return (free_and_msg(pr->pipes
					, pr->pids, pr->len_cmdb - 1, "fork"));
		if (pr->pids[i] == 0)
		{
			if (close_pipes(pr, i) == -1)
				return (-1);
			if (open_fd(pr, (*frame)->cmdblk, i) == -1)
				return (free_pipes_pids(pr->pipes
						, pr->pids, pr->len_cmdb - 1, -1));
			if (pipex(pr, frame, next_cmdb(i, &(*frame)->cmdblk)) == -1)
				return (-1);
		}
	}
	return (pipex_status(frame, pr));
}
