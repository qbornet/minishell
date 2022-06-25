/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:30:06 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:30:06 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cwd)
	{
		if (write(1, cwd, ft_strlen(cwd)) < 0)
			return (-1);
		if (write(1, "\n", 1) < 0)
			return (-1);
		free(cwd);
		return (0);
	}
	return (-1);
}
