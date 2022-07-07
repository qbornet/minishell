#include <minishell.h>

static int	ft_isstar(int to_do, t_strlist *tmp)
{
	while (to_do && tmp && !tmp->s_id)
	{
		tmp = tmp->next;
		to_do--;
	}
	if (!tmp || !tmp->s_id)
		return (1);
	return (0);
}

static size_t	ft_check_isstar(int to_do, t_strlist **s_curr)
{
	size_t			i;
	t_strlist		*strlst;

	i = 0;
	strlst = *s_curr;
	if (ft_isstar(to_do, strlst))
		return (to_do);
	while (to_do && strlst)
	{
		while (strlst && strlst->s_id)
		{
			i++;
			strlst = strlst->next;
		}
		to_do--;
		if (to_do && strlst && !strlst->s_id)
		{
			i++;
			strlst = strlst->next;
		}
	}
	return (i);
}

static int	ft_cmd_str(int to_do, size_t index
		, t_strlist **strlst, t_data **d_curr)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_check_isstar(to_do, strlst);
	(*d_curr)->cmd_pool[index] = ft_calloc(len + 1, sizeof(char *));
	if (!(*d_curr)->cmd_pool[index])
		return (-1);
	while (len > 0 && (*strlst))
	{
		(*d_curr)->cmd_pool[index][i] = (*strlst)->data;
		len--;
		i++;
		*strlst = (*strlst)->next;
	}
	return (0);
}

int	ft_create_cmd(t_data **d_curr, int total_cmd)
{
	int			to_do;
	size_t		index;
	t_lenlist	*lengthlst;
	t_strlist	*strlst;

	index = 0;
	strlst = (*d_curr)->strlst;
	lengthlst = (*d_curr)->lenlst;
	while (total_cmd && lengthlst)
	{
		to_do = lengthlst->length;
		if (ft_cmd_str(to_do, index, &strlst, d_curr) < 0)
			return (-1);
		total_cmd--;
		index++;
		lengthlst = lengthlst->next;
	}
	return (0);
}
