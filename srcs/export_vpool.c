#include <minishell.h>

static int	ft_search_equals(char *var)
{
	char	*varcpy;

	varcpy = var;
	while (*varcpy && *varcpy != '=')
		varcpy++;
	if (!*varcpy)
		return (0);
	return (1);
}

static int	ft_replace_var(char **v_curr, char **var_pool)
{
	char	*var;
	size_t	i;

	i = -1;
	var = *v_curr;
	while (var_pool[++i])
	{
		if (!ft_strncmp(var, var_pool[i], ft_strlen(var)))
		{
			free(var);
			var = ft_strdup(var_pool[i]);
			if (!var)
				return (-1);
			*v_curr = var;
			return (0);
		}
	}
	return (-1);
}

char	*search_varpool(char *var, char **var_pool)
{
	char	*dup;

	dup = ft_strdup(var);
	if (!dup)
		return (NULL);
	if (ft_search_equals(dup))
		return (dup);
	if (ft_replace_var(&var, var_pool) < 0)
	{
		free(dup);
		return (NULL);
	}
	free(dup);
	return (var);
}
