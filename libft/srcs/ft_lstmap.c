/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:18:42 by jfrancai          #+#    #+#             */
/*   Updated: 2021/11/30 17:53:03 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*result;
	t_list	*next;

	temp = ft_lstnew(f(lst->content));
	if (!temp)
		return (NULL);
	next = lst->next;
	result = temp;
	while (next)
	{
		temp = ft_lstnew(f(next->content));
		if (!temp)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		next = next->next;
		ft_lstadd_back(&result, temp);
	}
	return (result);
}
