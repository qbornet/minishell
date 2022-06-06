/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:52:49 by jfrancai          #+#    #+#             */
/*   Updated: 2022/03/01 10:34:51 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	free_and_return(int **tab1, int *tab2, int index, int return_val)
{
	free_int_tab(tab1, index);
	free_int(tab2);
	return (return_val);
}

int	free_and_msg(int **tab1, int *tab2, int index, char *msg)
{
	free_int_tab(tab1, index);
	free_int(tab2);
	return (error(msg));
}
