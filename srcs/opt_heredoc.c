#include <minishell.h>

static char	*ft_remove(char *str, size_t i)
{
	char	*end_str;
	char	*begin_str;
	char	*new_str;

	begin_str = ft_substr(str, 0, (i - 1));
	if (!begin_str)
		return (NULL);
	end_str = ft_substr(str, i, ft_strlen(str));
	if (!end_str)
		return (ft_error_malloc(((char *[]){begin_str, NULL})));
	new_str = ft_strjoin(begin_str, end_str);
	if (!new_str)
		return (ft_error_malloc(((char *[]){begin_str, end_str, NULL})));
	opt_free_doexpand(str, begin_str, end_str);
	return (new_str);
}

int		ft_isexit_heredoc(char *str)
{
	if (str[0] == '?' && (!ft_isprint(str[1] || !str[1])))
		return (1);
	return (0);
}

void	opt_free_doexpand(char *str, char *begin_str, char *end_str)
{
	if (str)
		free(str);
	if (begin_str)
		free(begin_str);
	if (end_str)
		free(end_str);
}

void	opt_find_dollars(char **s_curr, ssize_t *i)
{
	char	*str;

	str = *s_curr;
	while (str[*i])
	{
		if (*i - 1 != -1)
		{
			if (str[*i] == '$' && str[*i - 1] == '\\')
			{
				str = ft_remove(str, *i);
				continue ;
			}
		}
		else if (str[*i] == '$')
			break ;
		*i += 1;
	}
	*s_curr = str;
}

int	opt_word(char **w_curr)
{
	char				*tmp;
	char				*word;
	struct sigaction	act;

	tmp = NULL;
	word = *w_curr;
	ft_memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = &heredoc_handler;
	if (sigaction(SIGINT, &act, NULL) < 0)
		return (-1);
	if (word[0] == '\"' || word[0] == '\'')
	{
		tmp = ft_substr(word, 1, (ft_strlen(word) - 2));
		if (!tmp)
			return (-1);
		free(word);
		word = tmp;
		*w_curr = word;
		return (0);
	}
	return (1);
}
