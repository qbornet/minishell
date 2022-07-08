/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:55:27 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 17:55:08 by qbornet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_home(char *var)
{
	size_t	i;
	char	*home;

	i = 0;
	while (var[i] != '=')
		i++;
	home = ft_substr(var, (i + 1), ft_strlen(var));
	if (!home)
		return (NULL);
	return (home);
}

static char	*opt_add_homes(char **str_curr, char *home, size_t pos)
{
	char	*begin_str;
	char	*str;

	str = *str_curr;
	begin_str = ft_substr(str, 0, pos);
	if (!begin_str)
		return (NULL);
	alloc_str(&str, home, pos, begin_str);
	free(begin_str);
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_add_homes(char **str_curr, char **envp)
{
	char	*str;
	char	*home;
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	home = NULL;
	str = *str_curr;
	while (str[pos] != '~')
		pos++;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME", 4))
			home = get_home(envp[i]);
		i++;
	}
	if (!home)
		home = DFL_HOME;
	str = opt_add_homes(&str, home, pos);
	free(home);
	if (!str)
		return (NULL);
	return (str);
}

int	ft_do_tilde(t_data **d_curr)
{
	t_data		*frame;
	t_strlist	*strlst;
	char		*str;

	frame = *d_curr;
	strlst = frame->strlst;
	while (strlst)
	{
		str = strlst->data;
		if (!str || !*str)
			return (0);
		if ((str[0] == '~' && str[1] == '/') || str[0] == '~')
		{
			strlst->data = ft_add_homes(&str, (*d_curr)->envp);
			if (!strlst->data)
				return (-1);
		}
		strlst = strlst->next;
	}
	return (0);
}
