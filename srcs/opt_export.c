/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:05:02 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 13:31:15 by jfrancai         ###   ########.fr       */
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

char	**opt_create_temp(char **envp, char **noeq, char **temp)
{
	size_t	i;
	size_t	index_envp;
	size_t	index_noeq;

	i = 0;
	index_envp = -1;
	index_noeq = -1;
	while (envp && envp[++index_envp])
	{
		temp[i] = ft_strdup(envp[index_envp]);
		if (!temp[i])
			return (free_temp(temp));
		i++;
	}
	while (noeq && noeq[++index_noeq])
	{
		temp[i] = ft_strdup(noeq[index_noeq]);
		if (!temp[i])
			return (free_temp(temp));
		i++;
	}
	return (temp);
}

int	opt_export(char *var)
{
	if (ft_strchr(var, '-') && !ft_strchr(var, '=') && ft_strlen(var) == 2)
	{
		ft_putstr_fd("export: no option for export ", 2);
		ft_putendl_fd(var, 2);
		free(var);
		g_exit_status = 2;
		return (-1);
	}
	return (0);
}
