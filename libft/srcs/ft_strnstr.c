/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 12:33:04 by jfrancai          #+#    #+#             */
/*   Updated: 2021/11/25 11:50:34 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	int		j;

	little_len = ft_strlen(little);
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
