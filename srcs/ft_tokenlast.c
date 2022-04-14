/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:21:06 by jfrancai          #+#    #+#             */
/*   Updated: 2022/04/14 14:19:10 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tokenlist	*ft_tokenlast(t_tokenlist *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
