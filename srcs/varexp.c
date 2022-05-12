#include "minishell.h"

int	ft_varlen(char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s && *s != '=')
		s++;
	return (s - tmp);
}

char	*check_var_env(char **env, char *var_name)
{
	if (!env)
		return (NULL);
	while (*env && ft_strncmp(*env, var_name, ft_varlen(*env)))
		env++;
	return (*env);
}

void	new_data(char *tmp, int len, t_strlist **strlst, char *result)
{
	int	size;

	size = len - ft_strlen(tmp);
	while (len--)
	{
		if (len >= size)
			result[len] = tmp[len - size];
		else
			result[len] = ((char *)(*strlst)->data)[len];
	}
}

char	*expand_var(char **s, t_strlist **strlst, char **env)
{
	int		len;
	char	*tmp;
	char	*result;

	result = NULL;
	tmp = check_var_env(env, *s + 1);
	if (tmp)
	{
		while (*tmp && *tmp != '=')
			tmp++;
		tmp++;
		len = *s - (char *)(*strlst)->data + ft_strlen(tmp);
		result = ft_calloc(len + 1, sizeof(char));
		if (!result)
			return (NULL);
		new_data(tmp, len, strlst, result);
	}
	return (result);
}

void	expand(t_strlist *strlst, char **env)
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
			result = expand_var(&s, &strlst, env);
			free(strlst->data);
			strlst->data = result;
		}
		strlst = strlst->next;
	}
}
