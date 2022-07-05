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
		|| c ==  '&'
		|| c == ';'
		|| c == '('
		|| c == ')'
		|| c == '<'
		|| c == '>'
		|| c == '/'
		|| c == '$' 
		|| c == '?'
		|| c == '\''
		|| c == '\"')
		return (1);
	return (0);
}

size_t	ft_len_metachar(char *s)
{
	int		flag;
	int		len;

	if (!s)
		return (0);
	flag = 1;
	len = 0;
	while (*s && (!is_metachar(*s) || flag))
	{
		if (*s == '?')
		{
			len--;
			flag = 0;
		}
		len++;
		s++;
	}
	return (len);
}

int		ft_isexit(char *s)
{
	if (s[1] == '?')
		return (1);
	return (0);
}

char	*opt_expandvar(char **tmp, char **s, t_data *frame, int *flag)
{
	char	*cpy;

	*tmp = NULL;
	if (ft_isexit(*s))
	{
		*tmp = ft_itoa(g_exit_status);
		*flag = 1;
		return (*tmp);
	}
	else if (!*tmp)
		*tmp = check_intab(frame->envp, *s + 1);
	else if (!*tmp)
	{
		*tmp = check_intab(frame->var_pool, *s + 1);
		*flag = 1;
	}
	cpy = *tmp;
	while (*tmp && **tmp && **tmp != '=')
		(*tmp)++;
	if (*tmp)
		(*tmp)++;
	return (cpy);
}
