/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 01:16:00 by jfrancai          #+#    #+#             */
/*   Updated: 2021/11/25 10:56:05 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;

	s = (char *)src;
	d = (char *)dest;
	if (!dest && !src)
		return (dest);
	while (n-- > 0)
	{
		if (d < s)
			*(d++) = *(s++);
		else
			*(d + n) = *(s + n);
	}
	return (dest);
}
