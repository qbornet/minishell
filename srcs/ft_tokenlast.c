/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:17 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:29:18 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokenlist	*ft_tokenlast(t_tokenlist *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
