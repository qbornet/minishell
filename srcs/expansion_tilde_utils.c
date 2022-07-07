/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:57:20 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 12:06:46 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*alloc_str(char **str, char *home, size_t pos, char *begin_str)
{
	char	*end_str;
	char	*tmp;

	end_str = ft_substr(*str, pos + 1, ft_strlen(*str));
	if (!end_str)
		return (NULL);
	free(*str);
	*str = ft_strjoin(begin_str, home);
	if (!*str)
	{
		free(end_str);
		return (NULL);
	}
	tmp = *str;
	*str = ft_strjoin(tmp, end_str);
	free(tmp);
	free(end_str);
	return (*str);
}
