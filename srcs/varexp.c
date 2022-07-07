/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:30:26 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 08:07:49 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	new_data(char **s, char *tmp, t_strlist **strlst, char *result)
{
	size_t	i;
	size_t	l_exp;
	size_t	l_varname;
	size_t	l_after_exp;
	size_t	l_before_exp;

	i = -1;
	l_exp = ft_strlen(tmp);
	l_before_exp = ft_len_onechar((char *)(*strlst)->data, '$');
	l_varname = ft_len_metachar((char *)(*strlst)->data
			+ l_before_exp + 1) + 1;
	l_after_exp = ft_strlen((char *)(*strlst)->data + l_before_exp + l_varname);
	while (++i < l_before_exp)
		result[i] = ((char *)(*strlst)->data)[i];
	i = -1;
	while (++i < l_exp)
		result[i + l_before_exp] = tmp[i];
	i = -1;
	if ((*s)[1] == '?')
		l_varname++;
	while (++i < l_after_exp)
	{
		result[i + l_before_exp + l_exp] = ((char *)(*strlst)->data)
		[i + l_before_exp + l_varname];
	}
}

static char	*expand_var(char **s, t_strlist **strlst, t_data *frame)
{
	int		len;
	int		flag;
	char	*tmp1;
	char	*tmp2;
	char	*result;

	flag = 0;
	result = NULL;
	tmp2 = opt_expandvar(&tmp1, s, frame, &flag);
	len = ft_strlen(tmp1) + ft_strlen((*strlst)->data) - ft_len_metachar(*s);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
	{
		if (flag)
			free(tmp2);
		return (NULL);
	}
	new_data(s, tmp1, strlst, result);
	if (flag)
		free(tmp2);
	return (result);
}

char	*check_intab(char **tab, char *var_name)
{
	size_t	len;
	size_t	var_len;

	if (!tab)
		return (NULL);
	var_len = ft_len_metachar(var_name);
	while (*tab)
	{
		len = ft_len_onechar(*tab, '=');
		if (len < var_len)
			len = var_len;
		if (!ft_strncmp(*tab, var_name, len))
			break ;
		tab++;
	}
	return (*tab);
}

static int	check_empty_dol(t_strlist *strlst, char **result)
{
	char	*tmp;

	if ((*result)[0] == '$')
	{
		tmp = strlst->data;
		strlst->data = ft_strjoin(strlst->data, "");
		free(tmp);
		free(*result);
		return (1);
	}
	free(strlst->data);
	strlst->data = *result;
	return (0);
}

void	expand(t_strlist *strlst, t_data **frame, int flag)
{
	char	*s;
	char	*result;

	s = (char *)strlst->data;
	while (*s && *s != '$')
		s++;
	while (*s)
	{
		if ((!s[1] || s[1] == ' ' || (flag && s[1] == '"')) && s[0] == '$')
			result = ft_strdup("$");
		else
			result = expand_var(&s, &strlst, *frame);
		if (!result)
			return ;
		if (check_empty_dol(strlst, &result))
			return ;
		s = (char *)strlst->data;
		while (*s && *s != '$')
			s++;
	}
}
