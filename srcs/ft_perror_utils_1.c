/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:47:10 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 11:43:39 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*error_126(const int status)
{
	g_exit_status = 126;
	if (status == E_IS_DIR_126)
		return ("Is a directory\n");
	if (status == E_DENIED)
		return ("Permission denied\n");
	return (NULL);
}

char	*error_127(const int status)
{
	g_exit_status = 127;
	if (status == E_NOT_FOUND)
		return ("command not found\n");
	if (status == E_NOT_EXIST)
		return ("No such file or directory\n");
	return (NULL);
}

char	*error_1(const int status)
{
	g_exit_status = 1;
	if (status == E_TOO_MARGS)
		return ("too many arguments\n");
	if (status == E_IS_DIR_1)
		return ("Is a directory\n");
	if (status == E_NOT_DIR_1)
		return ("Not a directory\n");
	if (status == E_DENIED_1)
		return ("Permission denied\n");
	if (status == E_NOT_EXIST_1)
		return ("No such file or directory\n");
	return (NULL);
}

char	*error_2(const int status)
{
	g_exit_status = 2;
	if (status == E_FORBIDDEN_0)
		return ("make sure not to use ) ( &\n");
	if (status == E_FORBIDDEN_1)
		return ("make sure not to use ||\n");
	if (status == E_TOK_CREA)
		return ("something went wrong in token creation\n");
	if (status == E_UNC_QUO)
		return ("unclosed quotes\n");
	if (status == E_SYNTAX)
		return ("syntax error near unexpected token ");
	if (status == E_INV_OPT)
		return ("invalid option\n");
	return (NULL);
}
