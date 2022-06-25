/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:29:30 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 12:09:40 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ret_res(t_cmdblock **c_curr, char *res, char *word)
{
	int			fd_val;
	char		*str;

	str = ft_random_str("/tmp/heredoc-", 8);
	if (!str)
		return (-1);
	fd_val = open(str, O_CREAT | O_EXCL | O_RDWR, 0644);
	if (fd_val == -1)
	{
		free(res);
		return (-1);
	}
	write(fd_val, res, ft_null(res));
	close(fd_val);
	free(res);
	return (ft_replace_node(&(*c_curr)->infile, word, str));
}

static char	*ft_strjoin_here(char *s1, char *s2)
{
	char	*str;
	char	*tmp;
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	tmp = s1;
	len_s1 = ft_strjoin_len(s1);
	len_s2 = ft_strjoin_len(s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	while (len_s1--)
		str[i++] = *s1++;
	while (len_s2--)
		str[i++] = *s2++;
	str[i] = '\0';
	if (tmp)
		free(tmp);
	return (str);
}

static char	*ft_strendl(char *str)
{
	size_t		i;
	char		*new_str;

	if (!str)
		return (NULL);
	i = ft_null(str);
	new_str = malloc(sizeof(char) * (i + 2));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	free(str);
	new_str[i] = '\n';
	new_str[i + 1] = '\0';
	return (new_str);
}

static char	*opt_here_doc(t_data **d_curr, char *str, int flag)
{
	int		to_do;
	size_t	i;

	i = 0;
	if (flag)
	{
		to_do = ft_num_expand(str);
		while (to_do--)
		{
			str = do_expand(d_curr, str);
			if (!str)
				return (ft_error_malloc(((char *[]){str, NULL})));
		}
		opt_find_dollars(&str, &i);
	}
	return (str);
}

int	here_doc(t_data **d_curr, t_cmdblock **c_curr, char *word)
{
	int		flag;
	char	*res;
	char	*str;

	res = NULL;
	flag = opt_word(&word);
	if (flag < 0)
		return (-1);
	while (1)
	{
		str = readline(HEREDOC_PROMPT);
		if (!ft_strcmp_here(str, word))
			break ;
		str = opt_here_doc(d_curr, str, flag);
		if (!str)
			return (ft_error_here(word));
		str = ft_strendl(str);
		if (!str)
			return (ft_error_here(word));
		res = ft_strjoin_here(res, str);
		free(str);
		str = NULL;
	}
	return (ret_res(c_curr, res, word));
}
