/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:28:55 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:28:56 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenadd_back(t_tokenlist **alst, t_tokenlist *new)
{
	t_tokenlist	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_tokenlast(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}
