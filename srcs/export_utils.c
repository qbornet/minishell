/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:28:01 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/27 14:29:34 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_env(char **old)
{
	long	i;

	i = -1;
	while (old[++i])
		if (old[i])
			free(old[i]);
	free(old);
	return (0);
}
