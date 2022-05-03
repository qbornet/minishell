/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 12:33:04 by jfrancai          #+#    #+#             */
/*   Updated: 2022/05/03 09:21:30 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		j;

	if (!*little)
		return ((char *)big);
	while (*big && len > 0)
	{
		j = 0;
		while (big[j] == little[j] && len - j > 0)
		{
			if (little[j + 1] == '\0')
				return ((char *)(big));
			j++;
		}
		big++;
		len--;
	}
	return (NULL);
}
