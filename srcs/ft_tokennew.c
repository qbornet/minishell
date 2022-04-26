/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokennew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:59:22 by jfrancai          #+#    #+#             */
/*   Updated: 2022/04/14 12:15:16 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenlist	*ft_tokennew(void *content)
{
	t_tokenlist	*lstnew;

	lstnew = malloc(sizeof(*lstnew));
	if (!lstnew)
		return (NULL);
	lstnew->token = content;
	lstnew->next = NULL;
	return (lstnew);
}
