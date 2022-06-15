/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:52:49 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/15 18:39:59 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_int(int *tab)
{
	free(tab);
	tab = NULL;
	return (NULL);
}

void	*free_int_tab(int **tab, int i)
{
	if (i < 0)
		return (NULL);
	while (tab[i])
	{
		free_int(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

int	free_pipes_pids(int **tab1, int *tab2, int p_len, int return_val)
{
	if (p_len)
		free_int_tab(tab1, 0);
	free_int(tab2);
	return (return_val);
}

int	free_and_msg(int **tab1, int *tab2, int index, char *msg)
{
	free_int_tab(tab1, index);
	free_int(tab2);
	return (error(msg));
}
