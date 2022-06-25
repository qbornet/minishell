/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:55:08 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 13:01:08 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *p1, const char *p2)
{
	unsigned char		c1;
	unsigned char		c2;
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char *)p1;
	s2 = (const unsigned char *)p2;
	c1 = (unsigned char) *s1++;
	c2 = (unsigned char) *s2++;
	if (c1 == '\0')
		return (c1 - c2);
	while (c1 == c2)
	{
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 == '\0')
			return (c1 - c2);
	}
	return (c1 - c2);
}
