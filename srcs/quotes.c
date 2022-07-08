/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:54:58 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 16:10:34 by qbornet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_quotes(char c, enum e_quote *type)
{
	int	is_quotes;

	is_quotes = 0;
	if (c == '\"' && *type == E_DOUBLE)
	{
		is_quotes = 1;
		*type = 0;
	}
	else if (c == '\"' && !*type)
	{
		is_quotes = 1;
		*type = E_DOUBLE;
	}
	if (c == '\'' && *type == E_SINGLE)
	{
		is_quotes = 1;
		*type = 0;
	}
	else if (c == '\'' && !*type)
	{
		is_quotes = 1;
		*type = E_SINGLE;
	}
	return (is_quotes);
}

static int	len_quotes(char *s, int *is_quotes)
{
	enum e_quote	type;
	int				len;

	type = 0;
	len = 0;
	while (*s)
	{
		if (check_quotes(*s, &type))
		{
			len--;
			*is_quotes = 1;
		}
		s++;
		len++;
	}
	return (len);
}

static int	update_data(char **s, char *old, int len)
{
	int				i;
	char			*new;
	enum e_quote	type;

	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (-1);
	i = 0;
	type = 0;
	old = *s;
	while (*old)
	{
		if (check_quotes(*old, &type))
			old++;
		else
		{
			new[i] = *old;
			i++;
			old++;
		}
	}
	*s = new;
	return (0);
}

char	*ft_removes_quotes(char **s)
{
	int				is_quotes;
	int				len;

	is_quotes = 0;
	len = len_quotes(*s, &is_quotes);
	if (is_quotes)
		if (update_data(s, *s, len) < 0)
			return (NULL);
	return (*s);
}
