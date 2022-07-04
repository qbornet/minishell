#include <minishell.h>

static void	new_data(char *tmp, t_strlist **strlst, char *result)
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
	while (++i < l_after_exp)
		result[i + l_before_exp + l_exp] = ((char *)(*strlst)->data)
		[i + l_before_exp + l_varname];
}

static char	*expand_var(char **s, t_strlist **strlst, char **env, t_data *frame)
{
	int		len;
	int		flag;
	char	*tmp;
	char	*result;

	flag = 0;
	result = NULL;
	if (!(*s)[1] && (*s)[0] == '$')
		return (ft_strdup("$"));
	opt_expandvar(&flag, &tmp, env, s);
	if (!tmp)
		tmp = check_intab(frame->var_pool, *s + 1);
	while (!flag && tmp && *tmp && *tmp != '=')
		tmp++;
	if (!flag && tmp)
		tmp++;
	len = ft_strlen(tmp) + ft_strlen((*strlst)->data) - ft_len_metachar(*s);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
	{
		free(tmp);
		return (NULL);
	}
	new_data(tmp, strlst, result);
	free(tmp);
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


void	expand(t_strlist *strlst, char **env, t_data **frame)
{
	char	*s;
	char	*result;

	s = (char *)strlst->data;
	while (*s && *s != '$')
		s++;
	while (*s)
	{
		result = expand_var(&s, &strlst, env, *frame);
		if (!result)
			return ;
		if (check_empty_dol(strlst, &result))
			return ;
		s = (char *)strlst->data;
		while (*s && *s != '$')
			s++;
	}
}
