#include <minishell.h>

static char	*get_home(char *var)
{
	size_t	i;
	char	*home;

	i = 0;
	while (var[i] != '=')
		i++;
	home = ft_substr(var, (i + 1), ft_strlen(var));
	if (!home)
		return (NULL);
	return (home);
}

static char	*opt_add_homes(char **str_curr, char *home, size_t pos)
{
	char	*begin_str;
	char	*end_str;
	char	*str;

	str = *str_curr;
	begin_str = ft_substr(str, 0, pos);
	if (!begin_str)
		return (NULL);
	end_str = ft_substr(str, pos + 1, ft_strlen(str));
	if (!end_str)
		return (NULL);
	free(str);
	str = ft_strjoin(begin_str, home);
	if (!str)
		return (NULL);
	str = ft_strjoin(str, end_str);
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_add_homes(char **str_curr, char **envp)
{
	char	*str;
	char	*home;
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	home = NULL;
	str = *str_curr;
	while (str[pos] != '~')
		pos++;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME", 4))
			home = get_home(envp[i]);
		i++;
	}
	if (!home)
		home = DFL_HOME;
	str = opt_add_homes(&str, home, pos);
	if (!str)
		return (NULL);
	return (str);
}

static int	ft_findquotes(char *str)
{
	if (str && (str[0] == '\'' || str[0] == '\"'))
		return (1);
	return (0);
}

int	ft_do_tilde(t_data **d_curr)
{
	t_data		*frame;
	t_strlist	*strlst;
	char		*str;
	char		*ret;

	frame = *d_curr;
	strlst = frame->strlst;
	while (strlst)
	{
		str = strlst->data;
		if (!str)
			return (0);
		ret = ft_strchr(str, '~');
		if (!ret)
			return (0);
		else if (ret && !ft_isalnum(*(ret + 1)) && !ft_isalnum(*(ret - 1)) && !ft_findquotes(str))
		{
			strlst->data = ft_add_homes(&str, (*d_curr)->envp);
			if (!strlst->data)
				return (-1);
		}
		strlst = strlst->next;
	}
	return (0);
}
