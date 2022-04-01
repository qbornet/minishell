#include "bin.h"
#include "libft/utils/libft.h"

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

/* Prend env, regarde pour var dans env et le retire.
 * Alloue de la memoire de facon approprie */

int	ft_unset(char *var, char ***env_curr)
{
	int		i;
	int		len;
	char 	**new;
	char	**envp;
	int		index_to_unset;

	envp = *env_curr;
	len = ft_len(envp) - 1;
	new = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (1);
	index_to_unset = index_match(var, envp);
	if (index_to_unset == -1)
		return (2);
	i = 0;
	while (i < len)
	{
		if (i == index_to_unset)
			envp++;
		new[i] = ft_strdup(*envp);
		envp++;
		i++;
	}
	new[i] = NULL;
	*env_curr = new;
	return (0);
}

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
