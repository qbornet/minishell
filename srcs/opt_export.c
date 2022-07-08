/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:05:02 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 11:05:03 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	opt_export(char *var)
{
	if (ft_strchr(var, '-') && !ft_strchr(var, '=') && ft_strlen(var) == 2)
	{
		ft_putstr_fd("export: no option for export ", 2);
		ft_putendl_fd(var, 2);
		free(var);
		g_exit_status = 2;
		return (-1);
	}
	return (0);
}
