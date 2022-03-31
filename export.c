#include "bin.h"
#include <stdio.h>

/*
 * Pour les cas d'erreur ils faudrait rajouter un flag pour checker si on a utiliser envp
 * (malloc par nous dans le process) pour etre sur d'avoir le droit de free et eviter des erreur */

static long	ft_len(char **envp)
{
	long	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/* char *var doit etre une string malloc, tout peut etre free au moment de l'exit,
 * ***env_curr est present pour avoir toujours l'orginal
 * et eviter d'avoir une erreur a longterme si on ajoute plusieur fois des variables avec export
 * ou unset des variables ce sera toujours a jour */

int	ft_export(char *var, char ***env_curr)
{
	long	i;
	char	**new;
	char	**temp;
	char	**envp;

	i = 0;
	envp = *env_curr;
	temp = envp;
	new = (char **)malloc(sizeof(char *) * (ft_len(envp) + 2));
	if (!new)
		return (1);
	while (envp[i])
	{
		new[i] = strdup(envp[i]);
		i++;
	}
	new[i++] = var;
	new[i] = NULL;
	*env_curr = new;
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
	ft_export(str, &envp);
	printf("-----------------------------------\n");
	for (int j = 0; envp[j]; j++)
		printf("%s\n", envp[j]);
	for (int i = 0; envp[i]; i++)
		if (envp[i])
			free(envp[i]);
	free(envp);
	return (0);
}

*/
