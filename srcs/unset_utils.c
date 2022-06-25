/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:30:24 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:30:25 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_len(char **pool)
{
	size_t	i;

	i = 0;
	while (pool[i])
		i++;
	return (i);
}

static void	ft_free_old(char **pool)
{
	size_t	i;

	i = -1;
	while (pool[++i])
		free(pool[i]);
	free(pool);
}

int	ft_recreate_envp(char ***envp_curr, ssize_t index_envp)
{
	char	**new;
	char	**envp;
	ssize_t	i;

	if (index_envp == -1)
		return (0);
	i = 0;
	envp = *envp_curr;
	new = ft_calloc((ft_len(envp) - 1), sizeof(char *));
	if (!new)
		return (-1);
	while (envp[i])
	{
		if (i == index_envp)
		{
			i++;
			continue ;
		}
		new[i] = envp[i];
		i++;
	}
	ft_free_old(envp);
	*envp_curr = new;
	return (0);
}

int	ft_recreate_vpool(char ***vpool_curr, ssize_t index_vpool)
{
	char	**new;
	char	**vpool;
	ssize_t	i;

	if (index_vpool == -1)
		return (0);
	i = 0;
	vpool = *vpool_curr;
	new = ft_calloc(ft_len(vpool) - 1, sizeof(char *));
	if (!new)
		return (-1);
	while (vpool[i])
	{
		if (i == index_vpool)
		{
			i++;
			continue ;
		}
		new[i] = vpool[i];
		i++;
	}
	ft_free_old(vpool);
	*vpool_curr = new;
	return (0);
}
