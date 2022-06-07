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

int	ft_do_starexp(t_data **d_curr)
{
	int			flag;
	char		*str;
	t_data		*frame;
	t_strlist	*strlst;

	str = "";
	frame = *d_curr;
	strlst = frame->strlst;
	while (strlst)
	{
		flag = 0;
		if (strlst->data)
			str = strlst->data;
		if (str[0] == '\"')
			flag = 1;
		else if (str[0] == '\'')
			flag = 2;
		if (!flag && strlst->data)
			strlst = starexp(&strlst, frame);
		if (!strlst)
			return (-1);
		strlst = strlst->next;
	}
	return (0);
}

void	ft_do_varexp(t_data **d_curr)
{
	int			flag;
	char		*str;
	t_data		*frame;
	t_strlist	*strlst;

	str = "";
	frame = *d_curr;
	strlst = frame->strlst;
	while (strlst)
	{
		flag = 0;
		if (strlst->data)
			str = strlst->data;
		if (str[0] == '\"')
			flag = 1;
		else if (str[0] == '\'')
			flag = 2;
		if ((flag == 1 || !flag) && strlst->data)
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
