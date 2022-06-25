/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:54 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:27:59 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_removes_quotes(t_strlist **s_curr)
{
	char		*new;
	t_strlist	*strlst;

	strlst = *s_curr;
	new = ft_substr(strlst->data, 1, (ft_strlen(strlst->data) - 2));
	if (!new)
		return (-1);
	free(strlst->data);
	strlst->data = new;
	return (0);
}

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
		if (str && (str[0] == '\'' || str[0] == '\"'))
			if (ft_removes_quotes(&strlst) < 0)
				return (-1);
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
