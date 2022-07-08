/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:54:48 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 11:54:49 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_perror(const char *s, const int code)
{
	int	status;

	if (code)
		status = code;
	else
		status = g_exit_status;
	write(2, "minishell: ", 12);
	if (s && status != E_SYNTAX)
	{
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
	}
	write(2, error_selec(status), ft_strlen(error_selec(status)));
	if (status == E_SYNTAX)
	{
		write(2, "`", 1);
		write(2, s, ft_strlen(s));
		write(2, "'\n", 2);
	}
}

int	ft_perror_ret(const char *s, const int code, const int rvalue)
{
	ft_perror(s, code);
	return (rvalue);
}

void	*ft_perror_ptr(const char *s, const int code, void *rvalue)
{
	ft_perror(s, code);
	return (rvalue);
}
