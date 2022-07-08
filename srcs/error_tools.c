/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:21:18 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 13:59:10 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unlink_tmpfiles(t_cmdblock *cmdblock)
{
	t_redirlist	*fd;

	while (cmdblock)
	{
		fd = cmdblock->fd;
		while (fd)
		{
			if (fd->type == E_DLESS)
				unlink(fd->str);
			fd = fd->next;
		}
		cmdblock = cmdblock->next;
	}
	return (0);
}
