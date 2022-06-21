#include <minishell.h>

static int	ft_addslash(char c)
{
	if (c == '\a' || c == '\b'
			|| c == '\e' || c == '\f'
			|| c == '\n' || c == '\r'
			|| c == '\t' || c == '\v'
			|| c == '\\' || c == '\''
			|| c == '\"' || c == '\?')
		return (1);
	return (0);
}

static char	*ft_escape_sequence(char *str)
{
	size_t	i;
	size_t	count;
	char	*new;

	i = -1;
	count = 0;
	while (str[++i])
		if (ft_addslash(str[i]))
			count++;
	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + count + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (ft_addslash(str[i + 1]))
			new[i++] = '\\';
		new[i] = str[i];
		i++;
	}
	free(str);
	return (new);
}

static int	ft_removes_quotes(t_strlist **s_curr)
{
	char		*new;
	t_strlist	*strlst;

	strlst = *s_curr;
	new = ft_substr(strlst->data, 1, (ft_strlen(strlst->data) - 2));
	if (!new)
		return (-1);
	free(strlst->data);
	new = ft_escape_sequence(new);
	if (!new)
		return (-1);
	strlst->data = new;
	return (0);
}

int	ft_do_quotes(t_data **d_curr)
{
	char		*str;
	t_data		*frame;
	t_strlist	*strlst;

	frame = *d_curr;
	strlst = frame->strlst;
	while (strlst)
	{
		str = strlst->data;
		if (str && (str[0] == '\'' || str[0] == '\"'))
			if (ft_removes_quotes(&strlst) < 0)
				return (-1);
		strlst = strlst->next;
	}
	return (0);
}

int	ft_check_pool(char *str, char **pool, int res)
{
	size_t	i;

	i = 0;
	if (res >= 0)
	{
		free(pool[res]);
		pool[res] = ft_strdup(str);
		if (!pool[res])
			return (-1);
		return (1);
	}
	else
	{
		while (pool[i])
			i++;
		pool[i] = ft_strdup(str);
		if (!pool)
			return (-1);
		return (1);
	}
	return (0);
}
