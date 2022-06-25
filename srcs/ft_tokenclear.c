/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:06 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:29:08 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenclear(t_tokenlist **lst, void (*del)(void *))
{
	t_tokenlist	*tmp;

	if (!lst || !del || !*lst)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_tokendelone(*lst, del);
		*lst = tmp;
	}
}
