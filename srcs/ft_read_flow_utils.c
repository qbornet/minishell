/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_flow_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:11:00 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 12:19:12 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	condition_0(enum e_token type, enum e_token type_next)
{
	if ((type == E_PIPE || type == E_LESS || type == E_GREAT
			|| type == E_DLESS || type == E_DGREAT)
		&& (type_next == E_ERROR || type_next == E_EOI))
		return (1);
	return (0);
}

int	condition_1(enum e_token type, enum e_token type_next)
{
	if (((type == E_LESS || type == E_GREAT || type == E_DLESS
				|| type == E_DGREAT)
			&& type_next != E_FD && type_next != E_WORD)
		|| (type == E_PIPE && type_next == E_PIPE))
		return (1);
	return (0);
}
