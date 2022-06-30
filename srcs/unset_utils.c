#include <minishell.h>

static size_t	ft_len(char **pool)
{
	size_t	i;

	i = 0;
	while (pool[i])
		i++;
	return (i);
}

int	ft_recreate_envp(char ***envp_curr, ssize_t index_envp)
{
	char	**new;
	char	**envp;
	ssize_t	i;

	envp = *envp_curr;
	if (index_envp == -1)
		return (0);
	i = 0;
	new = ft_calloc((ft_len(envp)), sizeof(char *));
	if (!new)
		return (-1);
	while (envp[i])
	{
		if (i == index_envp)
		{
			free(envp[i++]);
			continue ;
		}
		new[i] = envp[i];
		i++;
	}
	*envp_curr = new;
	return (0);
}

int	ft_recreate_vpool(char ***vpool_curr, ssize_t index_vpool)
{
	char	**new;
	char	**vpool;
	ssize_t	i;

	if (index_vpool == -1)
		return (0);
	i = 0;
	vpool = *vpool_curr;
	new = ft_calloc(4096, sizeof(char *));
	if (!new)
		return (-1);
	while (vpool[i])
	{
		if (i == index_vpool)
		{
			free(vpool[i++]);
			continue ;
		}
		new[i] = vpool[i];
		i++;
	}
	*vpool_curr = new;
	return (0);
}
