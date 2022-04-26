#include "minishell.h"

char	*free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}

char	*free_tab(char **tab)
{
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
	return (NULL);
}

char	*free_elt_tab(char **tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		free_str(tab[i]);
		i++;
	}
	return (NULL);
}

char	*free_str_tab(char **tab, int index)
{
	free_elt_tab(tab + index);
	return (free_tab(tab));
}
