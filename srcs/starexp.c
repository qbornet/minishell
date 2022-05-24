#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>

int	ft_strstarcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	lens2;
	int		cmp;

	i = 0;
	while (s1[i] && s1[i] != '*')
		i++;
	if (i > n - 1)
	{
	//	printf("end 0\n");
		return (ft_strncmp(s1, s2, n));
	}
	cmp = ft_strncmp(s1, s2, i);
	if (cmp)
	{
	//	printf("end 1\n");
		return (1);
	}
	lens2 = ft_strlen(s2);
	j = 0;
	while (s1[i])
	{
		while (s1[i] == '*')
			i++;
		len = 0;
		while (s1[i + len] && s1[i + len] != '*')
			len++;
		cmp = ft_strncmp(s1 + i, s2 + j, len);
		while (s2[j] && cmp && j + len < lens2)
		{
			j++;
			cmp = ft_strncmp(s1 + i, s2 + j, len);
		}
		if (cmp)
		{
	//		printf("end 2 \n");
			return (1);
		}
		i += len;
		j += len;
	}
	if (cmp)
	{
	//	printf("end 3\n");
		return (1);
	}
	return (cmp);
}

int	get_file(char *s)
{
	size_t			len;
	size_t			l;
	DIR				*dir;
	struct dirent	*dr;

	len = ft_strlen(s);
	dir = opendir(".");
	dr = readdir(dir);
	while (dr)
	{
		l = len;
		if (ft_strlen(dr->d_name) >= len)
			l = ft_strlen(dr->d_name);
		if (!ft_strstarcmp(s, dr->d_name, l))
			printf("%s\n", dr->d_name);
		dr = readdir(dir);
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Provide args\n");
		return (-1);
	}
	get_file(av[1]);
	return (0);
}
