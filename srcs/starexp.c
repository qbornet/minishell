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
	if (!*tab)
		return (0);
	(*tab)[0] = NULL;
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

static int	s_exp(char *s, char ***tab, DIR *dir)
{
	struct dirent	*dr;

	if (!init_starexp(tab, &dir, &dr))
		return (-1);
	if (!is_star(s))
		return (closedir(dir));
	while (dr)
	{
		while ((dr->d_name)[0] == '.' && s[0] != '.')
			dr = readdir(dir);
		if (is_star(s) && !ft_starcmp(s, dr->d_name))
		{
			if (!add_str(tab, dr->d_name))
				return (closedir(dir));
		}
		dr = readdir(dir);
	}
	return (closedir(dir));
}

t_strlist	*starexp(t_strlist **strlst, t_data *frame, unsigned int *s_id)
{
	int			len;
	char		**tab;
	t_strlist	*head;

	if (s_exp((char *)(*strlst)->data, &tab, NULL))
		return (NULL);
	len = 0;
	while (tab[len])
		len++;
	ft_qsort(tab, 0, len - 1);
	len = 0;
	head = NULL;
	while (tab[len])
	{
		if (ft_strlst_addback(&head, tab[len], E_STAR) == -1)
		{
			ft_strclear(&head, free);
			free(tab);
			return (NULL);
		}
		len++;
	}
	free(tab);
	return (insert_strlst(strlst, &head, frame, s_id));
}
