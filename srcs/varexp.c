#include "minishell.h"

size_t	ft_varlen(char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s && *s != '=')
		s++;
	return (s - tmp);
}

char	*check_intab(char **tab, char *var_name)
{
	size_t	len;
	size_t	var_len;

	if (!tab)
		return (NULL);
	var_len = ft_strlen(var_name);
	while (*tab)
	{
		len = ft_varlen(*tab);
		if (len < var_len)
			len = var_len;
		if (!ft_strncmp(*tab, var_name, len))
			break ;
		tab++;
	}
	return (*tab);
}

void	new_data(char *tmp, int len, t_strlist **strlst, char *result)
{
	int	size;

	size = len - ft_strlen(tmp);
	while (len--)
	{
		if (tmp && len >= size)
			result[len] = tmp[len - size];
		else
			result[len] = ((char *)(*strlst)->data)[len];
	}
}

char	*expand_var(char **s, t_strlist **strlst, char **env, t_data *frame)
{
	int		len;
	char	*tmp;
	char	*result;

	result = NULL;
	tmp = check_intab(env, *s + 1);
	if (!tmp)
		check_intab(frame->var_pool, *s + 1);
	while (tmp && *tmp && *tmp != '=')
		tmp++;
	if (tmp)
		tmp++;
	len = *s - (char *)(*strlst)->data + ft_strlen(tmp);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	new_data(tmp, len, strlst, result);
	return (result);
}

void	expand(t_strlist *strlst, char **env, t_data *frame)
{
	char	*s;
	char	*result;

	while (strlst)
	{
		s = (char *)strlst->data;
		while (*s && *s != '$')
			s++;
		if (*s == '$')
		{
			result = expand_var(&s, &strlst, env, frame);
			free(strlst->data);
			strlst->data = result;
		}
		strlst = strlst->next;
	}
}
