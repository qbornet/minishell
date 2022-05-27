#include "minishell.h"

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
		|| c == '>')
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


