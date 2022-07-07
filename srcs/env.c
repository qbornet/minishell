/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:23 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 07:14:00 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(t_cmdblock *cmdblk, char **envp)
{
	int	i;

	if (!envp)
		return (0);
	if (cmdblk->cmd[1] != NULL)
		return (ft_perror_ret(cmdblk->cmd[1], E_DENIED, -1));
	i = 0;
	while (envp[i])
	{
		if (write(STDOUT_FILENO, envp[i], ft_strlen(envp[i])) == -1)
			return (-1);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
