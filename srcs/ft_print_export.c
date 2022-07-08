/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:05:30 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 11:07:44 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**free_temp(char **temp)
{
	size_t	i;

	i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	return (NULL);
}

static char	**ft_create_temp(char **envp, char **noeq)
{
	char	**temp;
	size_t	i;
	size_t	len_envp;
	size_t	len_noeq;

	i = -1;
	len_envp = 0;
	len_noeq = 0;
	while (envp && envp[len_envp])
		len_envp++;
	while (noeq && noeq[len_noeq])
		len_noeq++;
	temp = ft_calloc(len_envp + len_noeq + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	len_envp = -1;
	while (envp && envp[++len_envp])
	{
		temp[++i] = ft_strdup(envp[len_envp]);
		if (!temp[i])
			return (free_temp(temp));
	}
	len_noeq = -1;
	while (noeq && noeq[++len_noeq])
	{
		temp[i] = ft_strdup(noeq[len_noeq]);
		if (!temp[i])
			return (free_temp(temp));
		i++;
	}
	return (temp);
}

int	ft_print_export(char **envp, char **noeq)
{
	char	**temp;
	size_t	i;

	i = 0;
	temp = ft_create_temp(envp, noeq);
	if (!temp)
		return (-1);
	while (temp[i])
		i++;
	ft_qsort(temp, 0, (i - 1));
	i = -1;
	while (temp[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(temp[i], 1);
	}
	free_temp(temp);
	return (0);
}

int	add_noeq(t_data **d_curr, char *var)
{
	size_t		i;
	static char	*noeq[4096];

	i = 0;
	while (noeq[i])
		i++;
	noeq[i] = var;
	(*d_curr)->noeq = noeq;
	return (0);
}
