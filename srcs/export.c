/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:28:05 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:28:06 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* TODO: ✔️ 
 * - Doit ajouter les variables deja presente dans var_pool si jamais = n'est pas present dans la l'input */

static size_t	ft_len(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	ft_free_env(char **old)
{
	long	i;

	i = -1;
	while (old[++i])
		if (old[i])
			free(old[i]);
	free(old);
	return (0);
}

static size_t	index_match(char *var, char **envp)
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
	if (start < 0)
		return (1);
	envp = *env_curr;
	free(envp[start]);
	envp[start] = var;
	*env_curr = envp;
	return (0);
}

static int	ft_export_var(char *var, t_data **d_curr)
{
	size_t	i;
	char	**new;
	char	**temp;

	i = -1;
	temp = (*d_curr)->envp;
	if (!*var)
		return (0);
	if (index_match(var, (*d_curr)->envp) >= 0)
		return (replace_env(var, &(*d_curr)->envp));
	var = search_varpool(var, (*d_curr)->var_pool);
	if (!var)
		return (0);
	new = ft_calloc((ft_len(temp) + 2), sizeof(char *));
	if (!new)
		return (-1);
	while (temp[++i])
	{
		new[i] = ft_strdup(temp[i]);
		if (!new[i])
			return (ft_dup_error(new));
	}
	new[i++] = var;
	(*d_curr)->envp = new;
	return (ft_free_env(temp));
}

int	ft_export(t_data **frame)
{
	int			i;
	char		*var;
	t_cmdblock *cmdblock;

	i = 1;
	cmdblock = (*frame)->cmdblk;
	while (cmdblock->cmd[i])
	{
		var = ft_strdup(cmdblock->cmd[i]);
		if (!var)
			return (-1);
		if (ft_export_var(var, frame))
			return (-1);
		i++;
	}
	return (0);
}

/*
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
*/
