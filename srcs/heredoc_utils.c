#include <minishell.h>

char	*ft_varexp(char *var, char **envp, char **var_pool)
{
	char	*str;
	size_t	i;

	i = 0;
	str = "";
	while (envp[i])
	{
		if (!ft_strncmp(var, envp[i], ft_strlen(var)))
		{
			str = (ft_strchr(envp[i], '=') + 1);
			return (str);
		}
		i++;
	}
	i = 0;
	while (var_pool[i])
	{
		if (!ft_strncmp(var, var_pool[i], ft_strlen(var)))
		{
			str = (ft_strchr(var_pool[i], '=') + 1);
			return (str);
		}
		i++;
	}
	return (str);
}

int	ft_replace_node(t_redirlist	**r_curr, char *word, char *tempfile)
{
	char		*str;
	size_t		i;
	t_redirlist	*redir;

	i = 0;
	redir = *r_curr;
	while (redir)
	{
		str = redir->str;
		if (!ft_strncmp(str, word, ft_strlen(str)))
		{
			free(redir->str);
			redir->str = tempfile;
			return (i);
		}
		i++;
		redir->next;
	}
	return (-1);
}

int	ft_strcmp_here(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
	{
		ft_putstr_fd("warning: read EOF\n", 2);
		return (0);
	}
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_null(char *str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strjoin_len(char *str)
{
	size_t	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
