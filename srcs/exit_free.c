/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:49 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:27:50 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_envp(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = ft_calloc((i + 2), sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			i = 0;
			while (new_env[i])
				free(new_env[i++]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	close_allfd(void)
{
	size_t	i;

	i = 0;
	while (i < OPEN_MAX)
	{
		close(i);
		i++;
	}
}

void	ft_free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

void	ft_free_cpool(char ***cpool)
{
	size_t	i;

	if (!cpool)
		return ;
	i = 0;
	while (cpool[i])
		free(cpool[i++]);
	free(cpool);
}

void	ft_free_vpool(char **var_pool)
{
	int	i;

	if (!var_pool)
		return ;
	i = -1;
	while (var_pool[++i])
		free(var_pool[i]);
	free(var_pool);
}
