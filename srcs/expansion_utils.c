#include <minishell.h>

static int	ft_listnew_back(t_list **alist)
{
	t_list	*head;

	head = *alist;
	while (head->next)
		head = head->next;
	head->next = ft_lstnew(0);
	if (!head->next)
		return (-1);
	return (0);
}

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

void	ft_do_varexp(t_data **d_curr)
{
	int			flag;
	t_data		*frame;
	t_strlist	*strlst;

	frame = *d_curr;
	strlst = frame->strlst;
	while (strlst)
	{
		flag = 0;
		if (strlst->data[0] == '\"')
			flag = 1;
		else if (strlst->data[0] == '\'')
			flag = 2;
		if (flag == 1 || !flag)
			expand(strlst, frame->envp, &frame);
		strlst = strlst->next;
	}
	*d_curr = frame;
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

size_t	ft_len_var(char *str)
{
	char	*str_cpy;

	str_cpy = str;
	while (*str_cpy != '=')
		str_cpy++;
	return (str_cpy - str);
}
