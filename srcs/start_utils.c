/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:31:03 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 12:08:42 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static ssize_t	ft_findshlvl(char **envp)
{
	size_t	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp("SHLVL", envp[i], 5))
			return (i);
	return (-1);
}

void	ft_free_all(t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	ft_lenclear(&frame->lenlst);
	ft_strclear(&frame->strlst, &free);
	ft_cmdclear(&frame->cmdblk);
	ft_tokenclear(&frame->tokenlst, &free);
	ft_treeclear(frame->root, &free);
	ft_free_cpool(frame->cmd_pool);
	ft_free_vpool(frame->var_pool);
	ft_free_envp(frame->envp);
	ft_free_envp(frame->noeq);
	free(frame->std_fd);
	free(frame);
	close_allfd();
}

char	**ft_checkenv(char **envp)
{
	size_t	i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	if (i)
		return (envp);
	new = ft_calloc(10, sizeof(char *));
	if (!new)
		return (NULL);
	if (!i)
	{
		new[0] = ft_strjoin("PWD=", getcwd(NULL, PATH_MAX));
		new[1] = ft_strdup("SHLVL=0");
		new[2] = ft_strdup(DEFAULT_PATH);
		new[3] = ft_strjoin("HOME=", DFL_HOME);
		if (!new[0] || !new[1]
			|| !new[2] || !new[3])
			return (NULL);
	}
	return (new);
}

int	ft_addlevel(char ***envp_curr)
{
	int		num;
	char	*s;
	char	**envp;
	ssize_t	i;
	size_t	j;

	envp = *envp_curr;
	i = ft_findshlvl(envp);
	if (i == -1)
		return (0);
	j = 0;
	while (envp[i][j] != '=')
		j++;
	num = ft_atoi(&envp[i][++j]);
	free(envp[i]);
	s = ft_itoa(++num);
	envp[i] = ft_strjoin("SHLVL=", s);
	free(s);
	if (!envp[i])
		return (-1);
	*envp_curr = envp;
	return (0);
}
