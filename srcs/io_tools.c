/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:18:21 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/08 09:04:54 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_file(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) < 0)
		return (-1);
	if (S_ISREG(statbuf.st_mode))
		return (1);
	return (0);
}

int	is_dir(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) < 0)
		return (-1);
	if (S_ISDIR(statbuf.st_mode))
		return (1);
	return (0);
}

int	is_dirfile(const char *path)
{
	int	f;
	int	d;
	
	f = is_file(path);
	d = is_dir(path);
	if (f < 0 || d < 0)
		return (-1);
	if (f || d)
		return (1);
	return (0);
}
