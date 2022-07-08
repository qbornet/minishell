#include <minishell.h>

static char	**free_temp(char **temp)
{
	size_t	i;

	i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	return (NULL);
}

static char	**ft_create_temp(char **envp, char **noeq)
{
	char	**temp;
	size_t	len_envp;
	size_t	len_noeq;

	len_envp = 0;
	len_noeq = 0;
	while (envp && envp[len_envp])
		len_envp++;
	while (noeq && noeq[len_noeq])
		len_noeq++;
	temp = ft_calloc(len_envp + len_noeq + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	return (opt_create_temp(envp, noeq, temp));
}

int	ft_print_export(char **envp, char **noeq)
{
	char	**temp;
	size_t	i;

	i = 0;
	temp = ft_create_temp(envp, noeq);
	if (!temp)
		return (-1);
	while (temp[i])
		i++;
	ft_qsort(temp, 0, (i - 1));
	i = -1;
	while (temp[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(temp[i], 1);
	}
	free_temp(temp);
	return (0);
}

int	add_noeq(t_data **d_curr, char *var)
{
	size_t		i;
	char		*temp;
	static char	*noeq[4096];

	i = 0;
	while (noeq[i])
		i++;
	temp = search_varpool(var, (*d_curr)->var_pool);
	if (temp && !ft_strcmp(var, temp))
	{
		free(var);
		free(temp);
		return (0);
	}
	noeq[i] = var;
	(*d_curr)->noeq = noeq;
	return (0);
}

