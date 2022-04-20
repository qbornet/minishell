/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlst_addback.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbornet <qbornet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:19:47 by qbornet           #+#    #+#             */
/*   Updated: 2022/04/20 08:17:23 by qbornet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ast.h"

t_wordlist	*ft_wordlst_new(void *data, enum e_token type)
{
	t_wordlist	*new;

	if (!data)
		return (NULL);
	new = ft_calloc(1, sizeof(t_wordlist));
	if (!new)
		return (NULL);
	new->data = data;
	new->type = type;
	return (new);
}

int	ft_wordlst_addback(t_wordlist **lst_curr, void *data, enum e_token type)
{
	t_wordlist	*head;

	if (!lst_curr)
		return (-1);
	head = *lst_curr;
	if (!head)
	{
		*lst_curr = ft_wordlst_new(data);
		if (!*lst_curr)
			return (-1);
	}
	while (head->next)
		head = head->next;
	head->next = ft_wordlst_new(data);
	if (!head->next)
		return (-1);
	head->next->type = type;
	head->next->prev = head;
	return (0);
}
