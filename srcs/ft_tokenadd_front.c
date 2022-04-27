/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:52:37 by jfrancai          #+#    #+#             */
/*   Updated: 2022/04/13 15:18:55 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenadd_front(t_tokenlist **alst, t_tokenlist *new)
{
	if (alst)
	{
		if (*alst)
			new->next = *alst;
		*alst = new;
	}
}
