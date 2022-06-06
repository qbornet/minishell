/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:50 by jfrancai          #+#    #+#             */
/*   Updated: 2022/02/28 12:07:20 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH", 4))
		i++;
	if (!env[i] || ft_strncmp(env[i], "PATH", 4))
		paths = ft_split(DEFAULT_PATH, ':');
	else
		paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*get_program_path(char **paths, char *pg_name)
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

char	*get_path(char **env, char *pg)
{
	char	**paths;
	char	*path;

	path = NULL;
	if (pg[0] == '/' || !ft_strncmp(pg, "./", 2) || !ft_strncmp(pg, "../", 3))
	{
		if (access(pg, F_OK) == 0)
			path = ft_strdup(pg);
	}
	else
	{
		paths = get_env_paths(env);
		if (!paths)
			return (NULL);
		path = get_program_path(paths, pg);
		free_str_tab(paths, 0);
	}
	return (path);
}

int	dup_inout(int new_in, int new_out)
{
	if (dup2(new_in, STDIN_FILENO) == -1)
		return (standard_error("dup_inout in"));
	if (dup2(new_out, STDOUT_FILENO) == -1)
		return (standard_error("dup_inout out"));
	return (0);
}

int	close_pipe(int *pd)
{
	if (close(pd[0]) == -1)
		return (standard_error("close_pipe pid[0]"));
	if (close(pd[1]) == -1)
		return (standard_error("close_pipe pid[1]"));
	return (0);
}
