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

int	ft_logic_lst(t_btree *tree, t_list **l_curr)
{
	t_list	*logiclst;

	logiclst = *l_curr;
	if (tree && tree->node)
	{
		if (ft_logic_lst(tree->left, &logiclst) < 0)
			return (-1);
		if (tree->node->type == E_AND_IF || tree->node->type == E_OR_IF)
			if (ft_listnew_back(&logiclst) < 0)
				return (-1);
		if (ft_logic_lst(tree->right, &logiclst) < 0)
			return (-1);
	}
	return (0);
}
