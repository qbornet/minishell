#include "minishell.h"

static int	is_star(char *s)
{
	while (*s)
	{
		if (*s == '*')
			return (1);
		s++;
	}
	return (0);
}

static char	*add_str(char ***ptr, char *s)
{
	char	*stmp;
	char	**ttmp;
	size_t	len;

	stmp = ft_strdup(s);
	if (!stmp)
		return (free_str_tab(*ptr, 0));
	len = 0;
	while ((*ptr)[len])
		len++;
	ttmp = malloc(sizeof(char *) * (len + 2));
	if (!ttmp)
	{
		free(stmp);
		return (free_str_tab(*ptr, 0));
	}
	len = -1;
	while ((*ptr)[++len])
		ttmp[len] = (*ptr)[len];
	ttmp[len] = stmp;
	ttmp[len + 1] = NULL;
	free(*ptr);
	(*ptr) = ttmp;
	return (NULL);
}

int	starexp(char *s, char ***tab)
{
	size_t			l;
	size_t			len;
	DIR				*dir;
	struct dirent	*dr;

	len = ft_strlen(s);
	dir = opendir(".");
	if (!dir)
		return (0);
	dr = readdir(dir);
	while (dr)
	{
		while ((dr->d_name)[0] == '.' && s[0] != '.')
			dr = readdir(dir);
		l = len;
		if (ft_strlen(dr->d_name) >= len)
			l = ft_strlen(dr->d_name);
		if (is_star(s) && !ft_starexp(s, dr->d_name, l))
			add_str(tab, dr->d_name);
		else if (!is_star(s) && !ft_strncmp(s, dr->d_name, l))
			add_str(tab, dr->d_name);
		dr = readdir(dir);
	}
	return (closedir(dir));
}

/*
int	main(int ac, char **av)
{
	char	**tab;
	int		i;

	if (ac != 2)
	{
		printf("Provide args\n");
		return (-1);
	}
	tab = malloc(sizeof(char *));
	if (!tab)
		return (0);
	tab[0] = NULL;
	starexp(av[1], &tab);
	i = 0;
	while (tab[i])
	{
		printf("%s ", tab[i]);
		i++;
	}
	free_str_tab(tab, 0);
	printf("\n");
	return (0);
}
*/
