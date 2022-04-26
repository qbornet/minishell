/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:13:21 by jfrancai          #+#    #+#             */
/*   Updated: 2021/11/30 17:48:43 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*trim;

	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	if ((size_t)i == ft_strlen(s1))
		return (ft_strdup(""));
	j = ft_strlen(s1) - 1;
	while (s1[j] && is_in_set(s1[j], set))
		j--;
	if (j == -1)
		i = 0;
	trim = ft_calloc((j - i) + 2, sizeof(char));
	if (!trim)
		return (NULL);
	k = 0;
	while (i <= j)
		trim[k++] = s1[i++];
	return (trim);
}
