/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:25 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 11:10:50 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_env_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i] || ft_strncmp(env[i], "PATH=", 5))
		paths = ft_split(DEFAULT_PATH, ':');
	else
		paths = ft_split(env[i] + 5, ':');
	return (paths);
}

static char	*get_program_path(char **paths, char *pg_name)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		free_str(paths[i]);
		paths[i] = ft_strjoin(tmp, pg_name);
		free_str(tmp);
		if (!paths[i])
			return (free_str_tab(paths, i + 1));
		if (access(paths[i], F_OK) == 0)
			return (ft_strdup(paths[i]));
		i++;
	}
	return (NULL);
}

static char	*set_path(char **env, char *pg)
{
	char	**paths;
	char	*path;

	paths = get_env_paths(env);
	if (!paths)
		return (NULL);
	path = get_program_path(paths, pg);
	if (!path)
	{
		free_str_tab(paths, 0);
		return ((char *)ft_perror_ptr(pg, E_NOT_FOUND, 0));
	}
	free_str_tab(paths, 0);
	return (path);
}

char	*get_path(char **env, char *pg)
{
	char	*path;

	path = NULL;
	if (pg[0] == '/' || !ft_strncmp(pg, ".", 1) || !ft_strncmp(pg, "..", 2))
	{
		if (!is_file(pg))
			return ((char *)ft_perror_ptr(pg, E_IS_DIR_126, 0));
		if (access(pg, F_OK) == 0)
			path = ft_strdup(pg);
		else
			return ((char *)ft_perror_ptr(pg, E_NOT_EXIST, 0));
	}
	else
		path = set_path(env, pg);
	return (path);
}
