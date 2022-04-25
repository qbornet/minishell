/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:41:01 by jfrancai          #+#    #+#             */
/*   Updated: 2022/04/16 11:57:13 by jfrancai         ###   ########.fr       */
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
