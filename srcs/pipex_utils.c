/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:50 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/10 13:18:25 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
