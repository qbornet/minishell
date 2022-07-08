/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:11 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 07:11:50 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_env_home(char **env)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "HOME=", 5))
		i++;
	if (env[i] && !ft_strncmp(env[i], "HOME=", 5))
		home = ft_strdup(env[i] + 5);
	return (home);
}

static int	chdir_home(char *home)
{
	if (chdir(home) < 0)
	{
		free(home);
		return (-1);
	}
	free(home);
	return (0);
}

int	ft_cd(const t_cmdblock *cmdblock, char **envp)
{
	char	*home;

	if (cmdblock->cmd[1] && cmdblock->cmd[2])
		return (ft_perror_ret(cmdblock->cmd[0], E_TOO_MARGS, -1));
	home = get_env_home(envp);
	if (!home && !cmdblock->cmd[1])
		return (0);
	if (!cmdblock->cmd[1] && home)
	{
		if (chdir_home(home) < 0)
			return (-1);
		return (0);
	}
	free(home);
	if (is_dir(cmdblock->cmd[1]) < 0)
		return (ft_perror_ret(cmdblock->cmd[1], E_NOT_EXIST_1, -1));
	else if (is_dir(cmdblock->cmd[1]))
	{
		if (chdir(cmdblock->cmd[1]) < 0)
			return (ft_perror_ret(cmdblock->cmd[1], E_DENIED_1, -1));
	}
	else
		return (ft_perror_ret(cmdblock->cmd[1], E_NOT_DIR_1, -1));
	return (0);
}
