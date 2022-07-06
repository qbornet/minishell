#include <minishell.h>

size_t	ft_len_onechar(char *s, char a)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s && *s != a)
		s++;
	return (s - tmp);
}

int	is_metachar(char c)
{
	if (c == ' '
		|| c == '	'
		|| c == '|'
		|| c == '&'
		|| c == ';'
		|| c == '='
		|| c == '('
		|| c == ')'
		|| c == '<'
		|| c == '*'
		|| c == '%'
		|| c == '>'
		|| c == '/'
		|| c == '['
		|| c == ']'
		|| c == '$'
		|| c == '?'
		|| c == '\''
		|| c == '\"')
		return (1);
	return (0);
}

size_t	ft_len_metachar(char *s)
{
	int		len;

	if (!s)
		return (0);
	len = 0;
	while (*s && (!is_metachar(*s) || (*s == '?' && len == 1)))
	{
		if (*s == '?' && len == 1)
			len--;
		len++;
		s++;
	}
	return (len);
}

char	*opt_expandvar(char **tmp, char **s, t_data *frame, int *flag)
{
	char	*cpy;

	*tmp = NULL;
	if ((*s)[1] == '?')
	{
		*tmp = ft_itoa(g_exit_status);
		*flag = 1;
		return (*tmp);
	}
	else if (ft_isdigit((*s)[1]))
	{
		*tmp = ft_strdup(*s + 2);
		*flag = 1;
		return (*tmp);
	}
	if (!*tmp)
		*tmp = check_intab(frame->envp, *s + 1);
	if (!*tmp)
		*tmp = check_intab(frame->var_pool, *s + 1);
	cpy = *tmp;
	while (*tmp && **tmp && **tmp != '=')
		(*tmp)++;
	if (*tmp)
		(*tmp)++;
	return (cpy);
}
