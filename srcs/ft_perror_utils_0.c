/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:46:46 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 11:47:40 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*error_selec(const int status)
{
	if (status < 410)
		return (error_126(status));
	if (status < 420)
		return (error_127(status));
	if (status < 430)
		return (error_2(status));
	if (status < 440)
		return (error_1(status));
	return (NULL);
}

int	err_msg(const char *s, const int len, const int code)
{
	char			*err_msg;

	err_msg = ft_calloc(len + 1, sizeof(char));
	if (!err_msg)
		return (-1);
	ft_strlcpy(err_msg, s, len + 1);
	ft_perror(err_msg, code);
	free(err_msg);
	return (1);
}
