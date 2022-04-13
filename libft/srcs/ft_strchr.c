/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 12:15:44 by jfrancai          #+#    #+#             */
/*   Updated: 2021/11/29 15:25:25 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	len;
	int	i;

	len = ft_strlen(s) + 1;
	i = -1;
	while (++i < len)
		if (s[i] == (char)c)
			return ((char *)(s + i));
	return (NULL);
}
