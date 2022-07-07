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

int	ft_recreate_envp(char ***envp_curr, ssize_t index_envp)
{
	char	**new;
	char	**envp;
	ssize_t	i;
	ssize_t	j;

	envp = *envp_curr;
	if (index_envp == -1)
		return (0);
	i = 0;
	j = 0;
	new = ft_calloc((ft_len(envp)), sizeof(char *));
	if (!new)
		return (-1);
	while (envp[i])
	{
		if (i == index_envp)
		{
			free(envp[i++]);
			continue ;
		}
		new[j++] = envp[i++];
	}
	*envp_curr = new;
	return (0);
}

int	ft_recreate_vpool(char ***vpool_curr, ssize_t index_vpool)
{
	char	**new;
	char	**vpool;
	ssize_t	i;
	ssize_t	j;

	if (index_vpool == -1)
		return (0);
	i = 0;
	j = 0;
	vpool = *vpool_curr;
	new = ft_calloc(4096, sizeof(char *));
	if (!new)
		return (-1);
	while (vpool[i])
	{
		if (i == index_vpool)
		{
			free(vpool[i++]);
			continue ;
		}
		new[j++] = vpool[i++];
	}
	*vpool_curr = new;
	return (0);
}
