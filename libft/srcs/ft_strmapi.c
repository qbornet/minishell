/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:10:59 by jfrancai          #+#    #+#             */
/*   Updated: 2021/11/27 17:02:15 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapi;
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(s);
	mapi = ft_strdup(s);
	if (!mapi)
		return (NULL);
	while (++i < len)
		mapi[i] = f(i, mapi[i]);
	return (mapi);
}
