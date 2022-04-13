/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:52:10 by jfrancai          #+#    #+#             */
/*   Updated: 2021/11/26 12:13:10 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;

	concat = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!concat)
		return (NULL);
	ft_strlcat(concat, s1, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strlcat(concat, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (concat);
}
