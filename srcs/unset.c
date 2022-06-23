#include "minishell.h"

/* TODO:
 * - Doit unset toute les variables qui ont le meme nom dans var_pool et envp */

static long	ft_len(char **envp)
{
	long	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/* Compare cmp_var et envp[i];
 * Retourne la position de var dans envp, -1 sinon */

static int	index_match(char *var, char **envp)
{
	char	*cmp_var;
	int		i;

	i = 0;
	cmp_var = ft_strjoin(var, "=");
	while (envp[i])
	{
		if (!ft_strncmp(cmp_var, envp[i], ft_strlen(var) + 1))
		{
			free(cmp_var);
			return (i);
		}
		i++;
	}
	free(cmp_var);
	return (-1);
}

static int	free_str_t(char **new, int last)
{
	while (last--)
		free(new[last]);
	return (-1);
}

/* Prend env, regarde pour var dans env et le retire.
 * Alloue de la memoire de facon approprie */
int	ft_unset_var(char *var, char ***env_curr)
{
	int		i;
	char	**envp;
	char	**new;
	int		index_to_unset;

	envp = *env_curr;
	new = (char **)malloc(sizeof(char *) * ft_len(envp));
	if (!new)
		return (1);
	index_to_unset = index_match(var, envp);
	if (index_to_unset == -1)
		return (2);
	i = 0;
	while (*envp)
	{
		if (i == index_to_unset)
			envp++;
		if (*envp)
		{
			new[i] = ft_strdup(*envp++);
			if (!new[i])
				return (free_str_t(new, i));
		}
		i++;
	}
	new[i] = NULL;
	*env_curr = new;
	return (0);
}

int	ft_unset(t_cmdblock *cmdblock, char ***envp)
{
	int		i;
	char	*var;

	i = 1;
	while (cmdblock->cmd[i])
	{
		var = ft_strdup(cmdblock->cmd[i]);
		if (!var)
			return (-1);
		if (ft_unset_var(var, envp))
			return (-1);
		i++;
	}
	return (0);
}

/*
int	main(int ac, char **av, char **envp)
{
	char	*str;

	if (ac != 2)
		return (-1);
	str = strdup(av[1]);
	printf("-----------------------------------\n");
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	ft_unset(str, &envp);
	printf("-----------------------------------\n");
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	for (int i = 0; envp[i]; i++)
		if (envp[i])
			free(envp[i]);
	free(envp);
	free(str);
	return (0);
}
*/
