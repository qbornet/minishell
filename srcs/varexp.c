#include "minishell.h"

char	*check_var(char **env, char *var_name, int len)
{
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], var_name, len))
	{
		i++;
	}
	return (env[i]);
}

int	ft_var_len(char *s)
{
	char *tmp;

	tmp = s;
	while (*s != ' ')
		s++;
	return (s - tmp);
}

char	*varexp(char *to_expand, char **env)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	(void)env;
	tmp = to_expand;
	while (*to_expand)
	{
		if (*to_expand == '$')
		{
			len = ft_var_len(to_expand);
			tmp2 = check_var(env, to_expand + 1, len - 1);
			tmp = ft_strjoin(
		}
		to_expand++;
	}
	return (tmp);
}

int	is_local_var(char **vars, char *to_find)
{
	while (*vars && ft_strncmp(*vars, to_find, ft_strlen(to_find)))
		vars++;
	if (!*vars)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	(void)env;
	(void)av;
	(void)ac;
	char *s = "Bonjour $NOM ! Comment tu vas ? Mon pseudo : $PSEUDO";
	char *tmp;

	tmp = varexp(s, env);
	printf("%s\n", tmp);
	//free(tmp);
	return (-1);
}
