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
	return (ttmp[len]);
}

static int	init_starexp(char ***tab, DIR **dir, struct dirent **dr)
{
	*tab = malloc(sizeof(char *));
	(*tab)[0] = NULL;
	if (!*tab)
		return (0);
	*dir = opendir(".");
	if (!dir)
	{
		free(*tab);
		return (0);
	}
	*dr = readdir(*dir);
	if (!*dr)
	{
		closedir(*dir);
		return (0);
	}
	return (1);
}

static int	s_exp(char *s, size_t len, char ***tab, DIR *dir)
{
	size_t			l;
	struct dirent	*dr;

	if (!init_starexp(tab, &dir, &dr))
		return (-1);
	while (dr)
	{
		while ((dr->d_name)[0] == '.' && s[0] != '.')
			dr = readdir(dir);
		l = len;
		if (ft_strlen(dr->d_name) >= len)
			l = ft_strlen(dr->d_name);
		if (is_star(s) && !ft_starexp(s, dr->d_name, l))
		{
			if (!add_str(tab, dr->d_name))
				return (closedir(dir));
		}
		else if (!is_star(s) && !ft_strncmp(s, dr->d_name, l))
		{
			if (add_str(tab, dr->d_name))
				return (closedir(dir));
		}
		dr = readdir(dir);
	}
	return (closedir(dir));
}

int	starexp(t_strlist **strlst)
{
	int			len;
	char		**tab;
	t_strlist	*head;

	if (s_exp((char *)(*strlst)->data, ft_strlen((*strlst)->data), &tab, NULL))
		return (-1);
	len = 0;
	while (tab[len])
		len++;
	ft_qsort(tab, 0, len - 1);
	len = 0;
	head = NULL;
	while (tab[len])
	{
		if (ft_strlst_addback(&head, tab[len], 0) == -1)
		{
			ft_strclear(&head, free);
			free(tab);
			return (-1);
		}
		len++;
	}
	insert_strlst(strlst, &head);
	free(tab);
	return (-1);
}
