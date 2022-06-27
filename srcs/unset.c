/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:30:22 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/27 14:01:13 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	index_match(char *var, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(var, envp[i], ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}

static long	index_match_vpool(char *var, char **var_pool)
{
	int		i;

	i = 0;
	while (var_pool[i])
	{
		if (!ft_strncmp(var, var_pool[i], ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_unset_var(t_data **d_curr, char *var)
{
	long	index_envp;
	long	index_vpool;

	index_envp = index_match(var, (*d_curr)->envp);
	index_vpool = index_match_vpool(var, (*d_curr)->var_pool);
	if (ft_recreate_envp(&(*d_curr)->envp, index_envp) < 0)
		return (1);
	if (ft_recreate_vpool(&(*d_curr)->var_pool, index_vpool) < 0)
		return (1);
	return (0);
}

int	ft_unset(t_data **frame)
{
	int			i;
	t_cmdblock	*cmdblock;

	i = 1;
	cmdblock = (*frame)->cmdblk;
	while (cmdblock->cmd[i])
	{
		if (ft_unset_var(frame, cmdblock->cmd[i]))
			return (-1);
		i++;
	}
	return (0);
}
