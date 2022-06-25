/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokendelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:12 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:29:13 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
