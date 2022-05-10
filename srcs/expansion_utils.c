#include <minishell.h>

static void	ft_change_node(t_strlist **s_curr, t_strlist **head_curr)
{
	t_strlist	*tmp;
	t_strlist	*strlst;
	t_strlist	*head;

	strlst = *s_curr;
	tmp = strlst;
	head = *head_curr;
	if (strlst->prev)
	{
		strlst->next->prev = strlst->prev;
		strlst->prev->next = strlst->next;
	}
	else if (!strlst->prev)
	{
		if (strlst->next)
			strlst->next->prev = NULL;
		head = strlst->next;
	}
	strlst = strlst->next;
	free(tmp);
	*head_curr = head;
	*s_curr = strlst;
}

size_t	ft_len_var(char *str)
{
	char	*str_cpy;

	str_cpy = str;
	while (*str_cpy != '=')
		str_cpy++;
	return (str_cpy - str);
}


void	ft_move_node(t_data **d_curr, t_strlist **s_curr)
{
	t_strlist	*strlst;
	t_strlist	*head;

	strlst = *s_curr;
	head = strlst;
	while (strlst)
	{
		if (!strlst->data)
			ft_change_node(&strlst, &head);
		else
			strlst = strlst->next;
	}
	(*d_curr)->strlst = head;
}
