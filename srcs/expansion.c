#include <minishell.h>

size_t	ft_len_var(char *str)
{
	char	*str_cpy;

	str_cpy = str;
	while (*str_cpy != '=')
		str_cpy++;
	return (str_cpy - str);
}

int	ft_var(char *str)
{
	int		fd;
	int		flag;
	char	*buff;
	char	*var;
	size_t	len;

	len = ft_len_var(str) + 1;
	fd = open("/tmp/.minishell_var.tmp", O_RDRW | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	buff = (char *)malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (-1);
	var = ft_substr(str, 0, len);
	if (!var_name)
		return (-1);
	while (read(fd, buff, len))
	{
		if (!ft_strncmp(buff, var, len))
		{
			flag = 1;
			break ;
		}
	}
	free(var);
	if (flag)
	{
		var = ft_substr(str, len, (ft_strlen(str) - len));
		write(fd, 
	}
	else
		return (ft_new_var(str, fd));
	return (0);
}

void	ft_search_expansion(t_data **d_curr)
{
	int			i;
	char		*str;
	t_frame		*frame;
	t_strlist	*strlst;

	i = 1;
	frame = *d_curr;
	while (strlst)
	{
		str = strlst->data;
		if (str && ft_strchr(str, '=') && !strlst->prev)
			if (ft_var(str) < 0)
				return (-1);
	}
}


int	start_expansion(t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	ft_search_expansion(&frame->strlst);
	return (0);
}
