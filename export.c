#include "bin.h"
#include <stdio.h>
#include "../libft/includes/libft.h"

static long	ft_len(char **envp)
{
	long	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	ft_free_envp(char **old)
{
	long	i;

	i = -1;
	while (old[++i])
		if (old[i])
			free(old[i]);
	free(old);
	return (0);
}

static long	index_match(char *var, char **envp)
{
	long	i;
	char	*endcpy;

	i = 0;
	endcpy = var;
	while (*endcpy && *endcpy != '=')
		endcpy++;
	if (!*endcpy)
		return (-1);
	while (envp[i])
	{
		if (!ft_strncmp(var, envp[i], (endcpy - var)))
			return (i);
		i++;
	}
	return (-1);
}

static int	replace_env(char *var, char ***env_curr)
{
	long	start;
	char	**envp;

	start = index_match(var, *env_curr);
	envp = *env_curr;
	free(envp[start]);
	envp[start] = var;
	*env_curr = envp;
	return (0);
}

/* char *var doit etre une string malloc, tout peut etre free au moment de l'exit,
 * ***env_curr est present pour avoir toujours l'orginal
 * et eviter d'avoir une erreur a longterme si on ajoute plusieur fois des variables avec export
 * ou unset des variables ce sera toujours a jour */

/* NOTE : ✔️ 
 * Rajouter un check pour voir si la variable existe. Si oui alors il faut remplacer sa valeur */

int	ft_export(char *var, char ***env_curr)
{
	long	i;
	char	**new;
	char	**temp;
	char	**envp;

	i = -1;
	envp = *env_curr;
	temp = envp;
	if (!*var)
		return (2);
	if (index_match(var, *env_curr) >= 0)
		return (replace_env(var, &envp));
	new = (char **)malloc(sizeof(char *) * (ft_len(envp) + 2));
	if (!new)
		return (ft_free_err(new, temp));
	while (envp[++i])
	{
		new[i] = strdup(envp[i]);
		if (!new[i])
			return (ft_free_err(new, temp));
	}
	new[i++] = var;
	new[i] = NULL;
	*env_curr = new;
	return (ft_free_envp(temp));
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	*str;
	char	**new;

	if (ac != 2)
		return (-1);
	new = (char **)calloc(ft_len(envp) + 2, sizeof(char *));
	for (i = 0; envp[i]; i++)
		new[i] = strdup(envp[i]);
	str = strdup(av[1]);
	printf("-----------------------------------\n");
	for (i = 0; new[i]; i++)
		printf("%s\n", envp[i]);
	ft_export(str, &new);
	printf("-----------------------------------\n");
	for (i = 0; new[i]; i++)
	{
		printf("%s\n", new[i]);
		if (new[i])
			free(new[i]);
	}
	free(new);
	return (0);
}
