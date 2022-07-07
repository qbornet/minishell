/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:54 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 07:48:52 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_do_quotes(t_data **d_curr)
{
	char		*str;
	t_data		*frame;
	t_strlist	*strlst;

	frame = *d_curr;
	strlst = frame->strlst;
	while (strlst)
	{
		str = strlst->data;
		if (str)
		{
			strlst->data = ft_removes_quotes((char **)&strlst->data);
			if (!strlst->data)
				return (-1);
		}
		strlst = strlst->next;
	}
	return (0);
}

int	ft_check_pool(char *str, char **pool, int res)
{
	size_t	i;

	i = 0;
	if (res >= 0)
	{
		free(pool[res]);
		pool[res] = ft_strdup(str);
		if (!pool[res])
			return (-1);
		return (1);
	}
	else
	{
		while (pool[i])
			i++;
		pool[i] = ft_strdup(str);
		if (!pool)
			return (-1);
		return (1);
	}
	return (0);
}

char	is_valid_id(char *s)
{
	if (!ft_isalpha(*s))
		return (0);
	while (*(++s))
	{
		if (*s == '=')
			break ;
		if (!ft_isalnum(*s))
			return (0);
	}
	return (1);
}
