/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:27:36 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 12:27:52 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	opt_strlst(t_btree *r, t_lenlist **len_curr, int *cmd)
{
	int			i;

	if (r->node->type == E_VALID_FILE || r->node->type == E_VALID_BUILTIN
		|| r->node->type == E_WORD)
	{
		i = ft_length_lst(r->node->tokenlst);
		if (!*cmd)
		{
			(*len_curr)->length = i;
			*cmd = 1;
		}
		return (0);
	}
	if (r->node->type == E_PIPE)
	{
		*len_curr = (*len_curr)->next;
		*cmd = 0;
	}
	return (0);
}
