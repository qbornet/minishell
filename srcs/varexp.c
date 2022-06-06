#include "minishell.h"

static char	*check_intab(char **tab, char *var_name)
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
	char	*tmp;
	char	*result;

	result = NULL;
	tmp = check_intab(frame->var_pool, *s + 1);
	if (!tmp)
		tmp = check_intab(env, *s + 1);
	while (tmp && *tmp && *tmp != '=')
		tmp++;
	if (tmp)
		tmp++;
	len = ft_strlen(tmp) + ft_strlen((char *)(*strlst)->data)
		- ft_len_metachar(*s);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	new_data(tmp, strlst, result);
	return (result);
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
		free(strlst->data);
		strlst->data = result;
		s = (char *)strlst->data;
		while (*s && *s != '$')
			s++;
	}
}
