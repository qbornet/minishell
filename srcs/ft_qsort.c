/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:28:30 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:28:32 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static char	downchar(char c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

static int	ft_qstrcmp(const char *s1, const char *s2)
{
	size_t	i;
	char	c1;
	char	c2;

	i = 1;
	c1 = downchar(s1[0]);
	c2 = downchar(s2[0]);
	while (c1 && c1 == c2)
	{
		c1 = downchar(s1[i]);
		c2 = downchar(s2[i]);
		i++;
	}
	return (c1 - c2);
}

static int	partition(char **tab, int start, int end)
{	
	int		i;
	int		j;

	i = start;
	j = start;
	while (j < end)
	{
		if (ft_qstrcmp(tab[j], tab[end]) < 0)
		{
			swap(tab + i, tab + j);
			i++;
		}
		j++;
	}
	swap(tab + i, tab + end);
	return (i);
}

void	ft_qsort(char **tab, int start, int end)
{
	int	pivot;

	if (start > end)
		return ;
	pivot = partition(tab, start, end);
	ft_qsort(tab, start, pivot - 1);
	ft_qsort(tab, pivot + 1, end);
}
