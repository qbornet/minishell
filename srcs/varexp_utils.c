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

size_t	ft_len_twochar(char *s, char a, char b)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s && (*s != a && *s != b))
		s++;
	return (s - tmp);
}


