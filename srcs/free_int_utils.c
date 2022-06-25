/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:28:16 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:28:17 by jfrancai         ###   ########.fr       */
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

int	free_and_msg(int **tab1, int *tab2, int p_len, char *msg)
{
	free_pipes_pids(tab1, tab2, p_len, -1);
	return (error(msg));
}
