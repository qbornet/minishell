/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:28:00 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:28:01 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_free_expan_error(t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	close(frame->std_fd->stdin);
	close(frame->std_fd->stdout);
	ft_lenclear(&frame->lenlst);
	ft_strclear(&frame->strlst, &free);
	ft_cmdclear(&frame->cmdblk);
	ft_tokenclear(&frame->tokenlst, &free);
	ft_treeclear(frame->root, &free);
	ft_free_cpool(frame->cmd_pool);
	ft_free_vpool(frame->var_pool);
	ft_free_envp(frame->envp);
	free(frame->std_fd);
	free(frame);
	return (-1);
}
