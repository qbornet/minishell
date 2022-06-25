/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokennew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:21 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:29:22 by jfrancai         ###   ########.fr       */
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
