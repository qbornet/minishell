#include "minishell.h"

static size_t	get_next_star(const char *s, size_t start)
{
	size_t	len;

	len = 0;
	while (s[start + len] && s[start + len] != '*')
		len++;
	return (len);
}

static size_t	get_end(const char *s, size_t start)
{
	while (s[start])
		start++;
	return (start);
}

static int	loop(size_t i, const char *s1, const char *s2, size_t lens2)
{
	size_t	j;
	int		cmp;
	size_t	len;

	j = i;
	while (1)
	{
		while (s1[i] == '*')
			i++;
		len = get_next_star(s1, i);
		if (!s1[i + len])
		{
			if (!s2[j] && len)
				return (1);
			return (ft_strncmp(s1 + i, s2 + get_end(s2, j) - len, len));
		}
		cmp = ft_strncmp(s1 + i, s2 + j, len);
		while (s2[j] && cmp && j + len < lens2)
			cmp = ft_strncmp(s1 + i, s2 + (++j), len);
		if (cmp)
			return (1);
		i += len;
		j += len;
	}
	return (1);
}

int	ft_starexp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		cmp;

	i = get_next_star(s1, 0);
	if (i > n - 1)
		return (ft_strncmp(s1, s2, n));
	cmp = ft_strncmp(s1, s2, i);
	if (cmp)
		return (cmp);
	return (loop(i, s1, s2, ft_strlen(s2)));
}
