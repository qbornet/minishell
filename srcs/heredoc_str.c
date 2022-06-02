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

char *ft_random_str(char *pathname, int bytes)
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
