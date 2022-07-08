#include <minishell.h>

static char	*ft_ret_random(char *pathname, char *bytes_str, int j)
{
	char	*str;

	bytes_str[j] = '\0';
	str = ft_strjoin(pathname, bytes_str);
	free(bytes_str);
	if (!str)
		return (NULL);
	return (str);
}

size_t	ft_num_expand(char *str)
{
	ssize_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == '$' && (i - 1 == -1 || str[i - 1] != '\\'))
			count++;
	return (count);
}

char	*get_end_exp(t_data **d_curr, char *end_str)
{
	char	*var;
	char	*end;
	char	*new_str;
	size_t	i;

	i = 1;
	while (end_str[i] && (ft_isalnum(end_str[i]) || end_str[i] == '?'))
		i++;
	var = ft_substr(end_str, 1, (i - 1));
	if (!*var)
		return (var);
	if (!var)
		return (NULL);
	var = ft_varexp(var, (*d_curr)->envp, (*d_curr)->var_pool);
	if (!var)
		return (NULL);
	end = ft_substr(end_str, i, (ft_strlen(end_str) - i));
	if (!end)
		return (ft_error_malloc(((char *[]){var, NULL})));
	new_str = ft_strjoin(var, end);
	if (!new_str)
		return (ft_error_malloc(((char *[]){var, end, NULL})));
	return (new_str);
}

char	*ft_random_str(char *pathname, int bytes)
{
	int		j;
	int		fd;
	char	*bytes_str;
	char	buff[4096];
	size_t	i;

	j = 0;
	i = -1;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes_str = malloc(sizeof(char) * (bytes + 1));
	if (!bytes_str)
		return (NULL);
	read(fd, buff, 4096);
	close(fd);
	while (buff[++i])
	{
		if (bytes && ft_isalnum(buff[i]))
		{
			bytes_str[j++] = buff[i++];
			bytes--;
		}
	}
	return (ft_ret_random(pathname, bytes_str, j));
}

char	*do_expand(t_data **d_curr, char *str)
{
	char	*new_str;
	char	*begin_str;
	char	*end_str;
	ssize_t	i;

	i = 0;
	opt_find_dollars(&str, &i);
	begin_str = ft_substr(str, 0, i);
	if (!begin_str)
		return (NULL);
	end_str = ft_substr(str, i, (ft_strlen(str) - i));
	if (!end_str)
		return (ft_error_malloc(((char *[]){begin_str, NULL})));
	end_str = get_end_exp(d_curr, end_str);
	if (!end_str)
		return (ft_error_malloc(((char *[]){begin_str, NULL})));
	new_str = ft_strjoin(begin_str, end_str);
	if (!new_str)
		return (ft_error_malloc(((char *[]){begin_str, end_str, NULL})));
	opt_free_doexpand(str, begin_str, end_str);
	return (new_str);
}
