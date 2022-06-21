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
		|| c == '$' 
		|| c == '*'
		|| c == '\''
		|| c == '\"')
		return (1);
	return (0);
}

size_t	ft_len_metachar(char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s && !is_metachar(*s))
		s++;
	return (s - tmp);
}

int		ft_isexit(char *s)
{
	if (s[1] == '?' && s[2] == '\0')
		return (1);
	return (0);
}

void	opt_expandvar(int *flag, char **tmp, char **env, char **s)
{
	if (ft_isexit(*s))
	{
		*tmp = ft_itoa(g_exit_status);
		*flag = 1;
	}
	else
		*tmp = check_intab(env, *s + 1);
}
