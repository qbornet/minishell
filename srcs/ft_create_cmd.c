#include <minishell.h>

static char	*opt_first(t_strlist **strlst)
{
	char	*tmp;
	char	*res;


	if (!(*strlst)->data)
	{
		res = ft_strjoin("", "");
		return (res);
	}
	if (!(*strlst)->next)
	{
		res = ft_strjoin((*strlst)->data, "");
		return (res);
	}
	res = ft_strjoin((*strlst)->data, " ");
	if (!res)
		return (NULL);
	tmp = res;
	res = ft_strjoin(res, (*strlst)->next->data);
	free(tmp);
	if (!res)
		return (NULL);
	*strlst = (*strlst)->next;
	return (res);
}

static char	*opt_second(char **r_curr, t_strlist **strlst)
{
	char	*tmp;
	char	*res;

	res = *r_curr;
	tmp = res;
	res = ft_strjoin(res, " ");
	free(tmp);
	if (!res)
		return (NULL);
	tmp = res;
	res = ft_strjoin(res, (*strlst)->data);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

static char	*ft_cmd_str(int to_do, t_strlist **strlst)
{
	char	*res;
	size_t	flag;

	flag = 0;
	while (to_do > 0 && *strlst)
	{
		if (!flag++)
		{
			res = opt_first(&(*strlst));
			if (!res)
				return (NULL);
			to_do -= 2;
		}
		else
		{
			res = opt_second(&res, &(*strlst));
			if (!res)
				return (NULL);
			to_do -= 1;
		}
		*strlst = (*strlst)->next;
	}
	return (res);
}

int	ft_create_cmd(t_data **d_curr, int total_cmd)
{
	int			i;
	int			to_do;
	char		*res;
	t_lenlist	*lengthlst;
	t_strlist	*strlst;

	i = 0;
	strlst = (*d_curr)->strlst;
	lengthlst = (*d_curr)->lenlst;
	while (total_cmd)
	{
		to_do = lengthlst->length;
		res = ft_cmd_str(to_do, &strlst);
		if (!res)
			return (-1);
		(*d_curr)->join[i] = ft_strdup(res);
		free(res);
		if (!(*d_curr)->join[i++])
			return (-1);
		total_cmd--;
	}
	return (0);
}
