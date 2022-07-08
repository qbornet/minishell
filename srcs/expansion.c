/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:52 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 11:07:15 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_ret_opt(char *var_cmp, char *var_name, int index)
{
	free(var_cmp);
	free(var_name);
	return (index);
}

static int	ft_ret_index(char *str, char **var_pool)
{
	int		i;
	char	*var_cmp;
	char	*var_name;
	size_t	len;

	i = -1;
	len = ft_len_var(str);
	var_name = ft_substr(str, 0, len);
	if (!var_name)
		return (-2);
	while (var_pool[++i])
	{
		var_cmp = ft_substr(var_pool[i], 0, (ft_len_var(var_pool[i]) + 1));
		if (!var_cmp)
		{
			free(var_name);
			return (-2);
		}
		if (!ft_strncmp(var_cmp, var_name, ft_strlen(var_name)))
			return (ft_ret_opt(var_cmp, var_name, i));
		free(var_cmp);
	}
	free(var_name);
	return (-1);
}

static int	ft_var(char *str, t_data **d_curr)
{
	int	res;

	res = ft_ret_index(str, (*d_curr)->var_pool);
	if (res == -2)
		return (-1);
	if (ft_check_pool(str, (*d_curr)->var_pool, res))
		return (1);
	return (0);
}

static int	ft_search_expansion(t_data **d_curr)
{
	char		*str;
	t_data		*frame;
	t_strlist	*s;

	frame = *d_curr;
	if (!frame->var_pool)
		frame->var_pool = ft_calloc(4096, sizeof(char *));
	s = frame->strlst;
	if (!frame->var_pool)
		return (ft_free_expan_error(&frame));
	while (s)
	{
		str = s->data;
		if (str && ft_strchr(str, '=') && is_valid_id(str)
			&& (!s->prev || !s->prev->data))
		{
			if (ft_var(str, &frame) < 0)
				return (ft_free_expan_error(&frame));
			free(s->data);
			s->data = NULL;
		}
		s = s->next;
	}
	return (0);
}

int	start_expansion(t_data **d_curr)
{
	if (ft_search_expansion(d_curr) < 0)
		return (-1);
	ft_do_varexp(d_curr);
	if (ft_do_tilde(d_curr) < 0)
		return (ft_free_expan_error(d_curr));
	if (ft_do_starexp(d_curr) < 0)
		return (ft_free_expan_error(d_curr));
	if (ft_do_quotes(d_curr) < 0)
		return (ft_free_expan_error(d_curr));
	if (ft_create_join(d_curr) < 0)
		return (ft_free_expan_error(d_curr));
	if (command_block(d_curr) < 0)
		return (ft_free_expan_error(d_curr));
	return (0);
}
