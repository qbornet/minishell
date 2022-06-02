#include <minishell.h>

static int	ret_res(t_termstd *fd, char *res)
{
	write(fd->stdin, res, ft_strlen(res));
	free(res);
	res = NULL;
	return (0);
}

static char *ft_strjoin_here(char *s1, char *s2)
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

int	here_doc(t_data **d_curr, char *word)
{
	char	*res;
	char	*str;

	res = NULL;
	str = "";
	while (1)
	{
		str = readline(HEREDOC_PROMPT);
		if (!ft_strcmp_here(str, word))
			break ;
		str = ft_strendl(str);
		if (!str)
		{
			free(word);
			return (-1);
		}
		res = ft_strjoin_here(res, str);
		free(str);
		str = NULL;
	}
	return (ret_res(&(*d_curr)->std_fd, res));
}
