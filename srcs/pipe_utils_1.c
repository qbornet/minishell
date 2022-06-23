/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:04:52 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/23 17:28:27 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pipes(t_process *pr, int i)
{
	int	pipes_len;
	int	j;

	pipes_len = pr->len_cmdb - 1;
	j = -1;
	if (i == 0)
		j = 0;
	else if (i == pipes_len)
		pipes_len--;
	while (++j < pipes_len)
	{
		if (i == 0 || i == pipes_len || (j != i && j != i - 1))
		{
			if (close_pipe(pr->pipes[j]) == -1)
			{	
				free_pipes_pids(pr->pipes, pr->pids, pipes_len, 1);
				ft_putendl_fd("close_pipes: error", 2);
				return (-1);
			}
		}
	}
	return (0);
}

static int	**malloc_and_open_pipes(int len)
{
	int	**p;

	p = malloc(sizeof(int *) * (len + 1));
	if (!p)
		return (NULL);
	p[len] = NULL;
	while (len--)
	{
		p[len] = malloc(sizeof(int) * 2);
		if (!p[len])
			return ((int **)free_int_tab(p, len));
		if (pipe(p[len]) == -1)
			return ((int **)free_int_tab(p, len));
	}
	return (p);
}

int	alloc_pipes_pids(t_process *pr)
{
	if (pr->len_cmdb> 0)
	{
		pr->pipes = malloc_and_open_pipes(pr->len_cmdb - 1);
		if (!pr->pipes)
			return (error("malloc_pipes: error"));
	}
	pr->pids = malloc(sizeof(int) * pr->len_cmdb);
	if (!pr->pids)
	{
		free_int_tab(pr->pipes, 0);
		return (error("malloc pids: error"));
	}
	return (0);
}
