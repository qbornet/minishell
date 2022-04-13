/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:23:59 by jfrancai          #+#    #+#             */
/*   Updated: 2022/04/13 15:26:06 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
