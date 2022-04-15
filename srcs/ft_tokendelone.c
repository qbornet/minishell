/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokendelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:08:17 by jfrancai          #+#    #+#             */
/*   Updated: 2022/04/15 11:41:24 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_tokendelone(t_tokenlist *lst, void (*del)(void *))
{
	if (!del)
		return ;
	if (lst)
	{
		del(lst->token);
		free(lst);
	}
}
