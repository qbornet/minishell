#include "minishell.h"

int	ft_varlen(char *s)
{
	char *tmp;

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

void	expand(t_strlist *strlst, char **env)
{
	char	*s;
	int		len;
	char	*tmp;
	int		tmplen;
	char	*result;

	while (strlst)
	{
		s = (char *)strlst->data;
		while (*s && *s != '$')
			s++;
		if (*s == '$')
		{
			tmp = check_var_env(env, s + 1);
			if (tmp)
			{
				while (*tmp && *tmp != '=')
					tmp++;
				tmp++;
				tmplen = ft_strlen(tmp);
				len = s - (char *)strlst->data + tmplen;
				tmplen = len - tmplen;
				result = ft_calloc(len + 1, sizeof(char));
				if (!result)
					return ;
				while (len--)
				{
					if (len >= tmplen)
						result[len] = tmp[len - tmplen];
					else
						result[len] = ((char *)strlst->data)[len];
				}
				free(strlst->data);	
				strlst->data = result;
			}
		}
		strlst = strlst->next;
	}
}
