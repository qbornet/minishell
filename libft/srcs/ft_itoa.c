/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:49:17 by jfrancai          #+#    #+#             */
/*   Updated: 2021/11/30 17:42:34 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	allocate_size(int n)
{
	int	allocation;

	allocation = 2;
	if (n < 0)
		allocation++;
	while (n / 10)
	{
		allocation++;
		n /= 10;
	}
	return (allocation);
}

char	*ft_itoa(int n)
{
	int		size;
	int		nbr;
	char	*itoa;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = allocate_size(n);
	itoa = malloc(sizeof(*itoa) * size);
	if (!itoa)
		return (NULL);
	itoa[--size] = '\0';
	nbr = n;
	if (nbr < 0)
		nbr = -nbr;
	while (size--)
	{
		itoa[size] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		itoa[0] = '-';
	return (itoa);
}
